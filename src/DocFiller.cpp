#include "DocFiller.h"

namespace geology
{

bool write_file(const std::string& strFileName, const std::vector<char>& vData)
{
    std::ofstream Stream(strFileName, std::ios::binary);

    if (!Stream)
    {
        std:: cout << "Cannot open file.\n";
        return false;
    }

    Stream.write(vData.data(), vData.size());
    Stream.close();

    return true;
}

DocFiller::DocFiller(const std::string& strPath)
    : m_Doc(strPath),
      m_vHeader(read_file("EmptyDoc\\EmptyDoc.docx"))
{
    m_Doc.open();
}

std::string DocFiller::makeFilledStr(const std::map<std::string, std::string>& mArgs)
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

void DocFiller::saveFilledDoc(const std::string& strDstName, const std::map<std::string, std::string>& mArgs)
{
    auto DstDoc = makeNewDoc(strDstName);

    {
        auto& DstParagraph = DstDoc.paragraphs();

        for (auto Paragraph = m_Doc.paragraphs(); Paragraph.has_next(); Paragraph.next())
            DstParagraph.insert_paragraph_after("");

        for (auto Paragraph = m_Doc.paragraphs(); Paragraph.has_next(); Paragraph.next())
        {
            auto Run = Paragraph.runs();

            auto Style = Paragraph.get_style();
            DstParagraph.set_style(Style);

            while (Run.has_next())
            {
                auto strText = procRunText(Run, mArgs);

                auto NewRun = DstParagraph.add_run(strText);

                NewRun.set_style(Run.get_style());

                Run.next();
            }

            DstParagraph.next();
        }
    }

    auto& DstTable = DstDoc.tables();

    for (auto Table = m_Doc.tables(); Table.has_next(); Table.next())
    {
        auto DstRow = DstTable.rows();
        for (auto Row = Table.rows(); Row.has_next(); Row.next())
        {
            auto DstCell = DstRow.cells();
            for (auto Cell = Row.cells(); Cell.has_next(); Cell.next())
            {
                auto& DstParagraph = DstCell.paragraphs();
                for (auto Paragraph = Cell.paragraphs(); Cell.has_next(); Cell.next())
                {
                    auto Run = Paragraph.runs();

                    auto Style = Paragraph.get_style();
                    DstParagraph.set_style(Style);

                    while (Run.has_next())
                    {
                        auto strText = procRunText(Run, mArgs);

                        auto NewRun = DstParagraph.add_run(strText);

                        NewRun.set_style(Run.get_style());

                        Run.next();
                    }

                    DstParagraph.next();
                }
                DstCell.next();
            }
            DstRow.next();
        }
        DstTable.next();
    }

    DstDoc.set_style(m_Doc.get_style());

    DstDoc.save();

//    return DstDoc;
}

duckx::Document DocFiller::makeNewDoc(const std::string& strName)
{
    write_file(strName, m_vHeader);

    duckx::Document NewDoc(strName);
    NewDoc.open();

    return NewDoc;
}

duckx::Run DocFiller::procRun(duckx::Run& rRun, const std::map<std::string, std::string>& mArgs)
{
    std::string strText = procRunText(rRun, mArgs);

    duckx::Run NewRun;
    NewRun.set_text(strText);
    NewRun.set_style(rRun.get_style());

    return NewRun;
}

std::string DocFiller::procRunText(duckx::Run& rRun, const std::map<std::string, std::string>& mArgs)
{
    std::string strText(rRun.get_text());
    auto uLeft = strText.find("[");
    if (std::string::npos != uLeft)
    {
        auto uRight = strText.find("]");
        while(rRun.has_next() && std::string::npos == uRight)
        {
            rRun.next();
            strText += rRun.get_text();
            uRight = strText.find("]");
        }
        auto strKey = strText.substr(uLeft + 1, uRight - uLeft - 1);
        auto it = mArgs.find(strKey);
        if (mArgs.end() != it)
            strText = strText.substr(0, uLeft) + it->second + strText.substr(uRight + 1);
    }
    return strText;
}

} // namespace geology
