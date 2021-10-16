#include "IDocFiller.h"

int main() {
    auto upFiller = geology::make_doc_filler("Example.docx");
//    std::cout << Filler.makeFilledStr({{"example", "one"}, {"example2", "two"}}) << std::endl;

    upFiller->saveFilledDoc("FilledDoc.docx",
                            {{"place", "Деревня Иваново"},
                             {"space", "50 м"},
                             {"full_name", "Иванов Иван Иванович"},
                             {"passport_number", "123456"},
                             {"passport_given", "Кем-то"},
                             {"phone", "+71231231212"},
                             {"email", "test@test.email"},
                             {"snils", "123456"},
                             {"id", "1"},
                             {"date", "11"},
                             {"month", "Январь"},
                             {"year", "2021"},
                            });

//    auto strXml = Doc.getXml();
//    std::vector<char> vData(strXml.begin(), strXml.end());
//    write_file("FilledDoc.xml", vData);

//    duckx::Document NewDoc("Example.docx");
//    NewDoc.open();

//    strXml = NewDoc.getXml();
//    vData.assign(strXml.begin(), strXml.end());
//    write_file("Example.xml", vData);

    return 0;    
}
