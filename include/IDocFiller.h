#pragma once

#include <map>
#include <vector>
#include <memory>

namespace geology
{

struct IDocFiller
{
//    virtual explicit DocFiller(const std::string& strPath) = 0;

    virtual ~IDocFiller() = default;

    virtual std::string makeFilledStr(const std::map<std::string, std::string>& mArgs) = 0;

    virtual void saveFilledDoc(const std::string& strDstName, const std::map<std::string, std::string>& mArgs) = 0;
};

std::unique_ptr<IDocFiller> make_doc_filler(const std::string& strPath);

std::vector<char> read_file(const std::string& strFileName);

} // namespace geology

