Qt MutiLang
- Add default language by designer
- Add TRANSLATIONS configuration to .pro file, just like TRANSLATIONS += zh_cn.ts;
- QtCreator->Tools->External->Qt Linguist->Updata Translations   generate .ts file in project path; 
- open .ts file by linguist.exe, and Complete translation task;
- QtCreator->Tools->External->Qt Linguist->Release Translations   generate .qm file in project path; 
- Create QTranslator object and load .qm file;
- Override ChangeEvent func, retranslate UI when recive LanguageChange Event;
- call qApp->installTranslator(&translator) func when you want change display language;

Tips
- QtCreator->Tools->External->Configure..-> add -no-obsolete arguments for lupdate, this can clear the expired entry for .ts file when execute lupdate.
- For parts that do not want to be affected by multiple languages, you can uncheck  translatable Options in that Widget's property list;