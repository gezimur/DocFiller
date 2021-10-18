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
      m_vHeader(read_file("..\\resources\\doc\\EmptyDoc.docx"))
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

    fillParagraphs(m_Doc.paragraphs(), DstDoc.paragraphs(), mArgs);

//    auto& DstTables = DstDoc.tables();

//    for (auto Table = m_Doc.tables(); Table.has_next(); Table.next())
//    {
//        auto& DstTable = DstTables.append(Table.get_style());

//        auto& DstRows = DstTable.rows();
//        for (auto Row = Table.rows(); Row.has_next(); Row.next())
//        {
//            auto& DstRow = DstRows.append(Row.get_style());
//            auto& DstCells = DstRow.cells();
//            for (auto Cell = Row.cells(); Cell.has_next(); Cell.next())
//            {
//                auto& DstCell = DstCells.append(Cell.get_style());

//                fillParagraphs(Cell.paragraphs(), DstCell.paragraphs(), mArgs);
//            }
//        }
//    }

    DstDoc.set_style(m_Doc.get_style());

    std::lock_guard<std::mutex> Locker(m_Mutex);

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

void DocFiller::fillParagraphs(duckx::Paragraph& rSrc, duckx::Paragraph& rDst, const std::map<std::string, std::string>& mArgs)
{
    for (auto Paragraph = rSrc; Paragraph.has_next(); Paragraph.next())
        rDst.append("", Paragraph.get_style());

    for (auto Paragraph = rSrc; Paragraph.has_next(); Paragraph.next())
    {
        auto Run = Paragraph.runs();

        auto Style = Paragraph.get_style();
        rDst.set_style(Style);
//        auto& DstP = rDst.append("", Paragraph.get_style());

        while (Run.has_next())
        {
            auto strText = procRunText(Run, mArgs);

            auto NewRun = rDst.add_run(strText);

            NewRun.set_style(Run.get_style());

            Run.next();
        }

        rDst.next();
    }
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
