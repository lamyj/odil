#include <string>
#include <vector>

#include <dcmtkpp/BasicDirectoryCreator.h>
#include <dcmtkpp/registry.h>

int main(int argc, char** argv)
{
    std::string const root(argv[1]);
    std::vector<std::string> const files(argv+2, argv+argc);

    dcmtkpp::BasicDirectoryCreator creator(root, files,
        {
            {"PATIENT", { {dcmtkpp::registry::PatientBirthDate, 3} }},
            {"STUDY", { {dcmtkpp::registry::PatientAge, 3} }},
            {"SERIES", { {dcmtkpp::registry::SeriesDescription, 3} }},
            {"IMAGE", { {dcmtkpp::registry::ImageType, 3} }},
        });

    creator();

    return 0;
}
