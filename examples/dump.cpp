#include <fstream>
#include <iostream>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include <dcmtkpp/conversion.h>
#include <dcmtkpp/registry.h>
#include <dcmtkpp/Reader.h>
#include <dcmtkpp/Writer.h>

struct Printer
{
    typedef void result_type;

    std::ostream & stream;
    std::string indent;

    Printer(std::ostream & stream, std::string const & indent="")
    : stream(stream), indent(indent)
    {
        // Nothing else
    }

    template<typename T>
    void operator()(T const & value) const
    {
        for(auto const & item: value)
        {
            this->stream << item << " ";
        }
    }

    void operator()(dcmtkpp::Value::DataSets const & value) const
    {
        this->stream << "\n";

        auto const last_it = --value.end();
        for(auto it=value.begin(); it!= value.end(); ++it)
        {
            Printer const printer(this->stream, this->indent+"  ");
            printer(*it);
            if(it != last_it)
            {
                this->stream << "----\n";
            }
        }
    }

    void operator()(dcmtkpp::Value::Binary const & value) const
    {
        this->stream << this->indent << "(binary)";
    }

    void operator()(dcmtkpp::DataSet const & data_set) const
    {
        for(auto const & item: data_set)
        {
            this->stream << this->indent << item.first << " " << as_string(item.second.vr) << " ";
            dcmtkpp::apply_visitor(*this, item.second.get_value());
            this->stream << "\n";
        }
    }
};

int main(int argc, char** argv)
{
    for(int i=1; i<argc; ++i)
    {
        std::ifstream stream(argv[i], std::ios::in | std::ios::binary);

        stream.seekg(0, stream.end);
        int const length = stream.tellg();
        stream.seekg(0, stream.beg);

        std::string string(length, ' ');
        stream.read(&string[0], string.size());
        std::istringstream string_stream(string);

        struct timespec begin;
        clock_gettime(CLOCK_REALTIME, &begin);

        std::pair<dcmtkpp::DataSet, dcmtkpp::DataSet> file;
        try
        {
            file = dcmtkpp::Reader::read_file(string_stream);
        }
        catch(std::exception & e)
        {
            std::cout << "Could not read " << argv[i] << ": " << e.what() << "\n";
        }

        auto const & meta_information = file.first;
        auto const & data_set = file.second;

        Printer printer(std::cout);
        printer(meta_information);
        std::cout << "\n";
        printer(data_set);
    }

    return 0;
}
