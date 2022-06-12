#include "config_edt.h"

using namespace edt_mps;
using namespace mps::fichier;

bool config_edt::creer(){
    doc_xml doc;
    auto iter = doc.begin();
    element_xml elt;
    elt.set_name("conf");
    *iter = elt;
    elt.set_name("directories");
    iter = doc.push_back(iter, elt);
    elt.set_name("default");
    elt.set_text(QDir::homePath()+"/edt/");
    iter = doc.push_back(iter, elt);
    iter.to_parent(2);
    elt.set_name("files");
    elt.set_text("");
    iter = doc.push_back(iter, elt);
    elt.set_name("databases");
    doc.push_back(iter, elt);

    write(doc);
    return true;
}

//! Renvoie le chemin du dossier par default.
QString config_edt::default_directory()
    {return get_vars(DEFAULT_DIRECTORY);}
