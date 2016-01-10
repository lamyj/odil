#include <string>
#include <vector>

#include <odil/BasicDirectoryCreator.h>
#include <odil/registry.h>

int main(int argc, char** argv)
{
    std::string const root(argv[1]);
    std::vector<std::string> const files(argv+2, argv+argc);

    odil::BasicDirectoryCreator creator(root, files,
        {
            {"PATIENT", { {odil::registry::PatientBirthDate, 3} }},
            {"STUDY", { {odil::registry::PatientAge, 3} }},
            {"SERIES", { {odil::registry::SeriesDescription, 3} }},
            {"IMAGE", { {odil::registry::ImageType, 3} }},
        });

    creator();

    return 0;
}
