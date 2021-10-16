#include "IDocFiller.h"

#include "DocFiller.h"

namespace geology
{

std::unique_ptr<IDocFiller> make_doc_filler(const std::string& strPath)
{
    return std::unique_ptr<IDocFiller>(new DocFiller(strPath));
}

std::vector<char> read_file(const std::string& strFileName)
{
    std::vector<char> vRes;
    std::ifstream Stream(strFileName, std::ios::in | std::ios::binary);

    if (!Stream)
    {
        std:: cout << "Cannot open file.\n";
        return {};
    }

    char ch;
    while (Stream)
    { // in будет нулем при достижении конца файла
        Stream.get(ch);
        vRes.push_back(ch);
    }
    Stream.close();

    return vRes;
}

} // namespace geology
