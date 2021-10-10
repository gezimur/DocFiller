#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#include <duckx.hpp>

class DocFiller
{
public:
    explicit DocFiller(const std::string& strPath)
        : m_Doc(strPath)
    {
        m_Doc.open();
    }

    std::string fillDoc_simple_str(const std::map<std::string, std::string>& mArgs)
    {
        std::string strRes;
        for (auto Paragraph = m_Doc.paragraphs(); Paragraph.has_next(); Paragraph.next())
        {
            auto Run = Paragraph.runs();
            while (Run.has_next())
            {
                std::string strPart(Run.get_text());
                auto uLeft = strPart.find("[");
                if (std::string::npos != uLeft)
                {
                    auto uRight = strPart.find("]");
                    while(Run.has_next() && std::string::npos == uRight)
                    {
                        Run.next();
                        strPart += Run.get_text();
                        uRight = strPart.find("]");
                    }
                    auto strKey = strPart.substr(uLeft + 1, uRight - 1);
                    auto it = mArgs.find(strKey);
                    if (mArgs.end() != it)
                        strPart = strPart.substr(0, uLeft) + it->second + strPart.substr(uRight + 1);
                }
                strRes += strPart;
                Run.next();
            }
            strRes += "\n";
        }
        return strRes;
    }

    duckx::Document fillDoc_doc(const std::map<std::string, std::string>& mArgs)
    {

    }

private:
    duckx::Document m_Doc;

};

int main() {
//    DocFiller Filler("Example.docx");
//    std::cout << Filler.fillDoc_simple_str({{"example", "one"}, {"example2", "two"}}) << std::endl;

//    auto strRes = doc.getRes();

    std::vector<char> vHeader;

    std::ifstream ReadStream("EmptyDoc.docx");
    std::string strBuf;
    while(std::getline(ReadStream, strBuf))
        vHeader.insert( vHeader.end(), strBuf.begin(), strBuf.end());

    ReadStream.close();

    std::string strNewDoc("NewDoc.docx");

    std::ofstream WriteStream(strNewDoc.c_str());
    WriteStream.write(vHeader.data(), vHeader.size());
    WriteStream.close();

    duckx::Document doc(strNewDoc);
    doc.open();

    duckx::Paragraph p = doc.paragraphs().insert_paragraph_after("Paragraph");
    p.add_run(" Run ", duckx::none);

    doc.save();

    return 0;    
}
