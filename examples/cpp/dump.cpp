#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

#include <odil/DataSet.h>
#include <odil/Reader.h>
#include <odil/Value.h>

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

    void operator()(odil::Value::DataSets const & value) const
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

    void operator()(odil::Value::Binary const &) const
    {
        this->stream << this->indent << "(binary)";
    }

    void operator()(std::shared_ptr<odil::DataSet> const & data_set) const
    {
        for(auto const & item: *data_set)
        {
            this->stream << this->indent << item.first << " " << as_string(item.second.vr) << " ";
            odil::apply_visitor(*this, item.second.get_value());
            this->stream << "\n";
        }
    }
};

int main(int argc, char** argv)
{
    for(int i=1; i<argc; ++i)
    {
        std::ifstream stream(argv[i], std::ios::in | std::ios::binary);

        std::pair<std::shared_ptr<odil::DataSet>, std::shared_ptr<odil::DataSet>> file;
        try
        {
            file = odil::Reader::read_file(stream);
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
