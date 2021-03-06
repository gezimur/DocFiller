#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <mutex>

#include <duckx.hpp>

#include "IDocFiller.h"

namespace geology
{

class DocFiller: public IDocFiller
{
public:
    explicit DocFiller(const std::string& strPath);

    std::string makeFilledStr(const std::map<std::string, std::string>& mArgs) final;

    void saveFilledDoc(const std::string& strDstName, const std::map<std::string, std::string>& mArgs) final;

private:
    duckx::Document makeNewDoc(const std::string& strName);

    void fillParagraphs(duckx::Paragraph& rSrc, duckx::Paragraph& rDst, const std::map<std::string, std::string>& mArgs);

    duckx::Run procRun(duckx::Run& rRun, const std::map<std::string, std::string>& mArgs);

    std::string procRunText(duckx::Run& rRun, const std::map<std::string, std::string>& mArgs);

    std::mutex m_Mutex;

    duckx::Document m_Doc;
    std::vector<char> m_vHeader;
};

} // namespace geology
