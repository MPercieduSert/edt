#include "fen_principale_edt.h"

using namespace edt_mps;

fen_principale_edt::fen_principale_edt(noyau_edt * noya, std::unique_ptr<bdd_edt> bdd,
                                       mps::fenetre::predef_zone_centrale * central_zone,
                                       const QString &bdd_path_xml, const QString & config_path, QWidget *parent)
        : predef_fen_principale (noya,std::move(bdd),central_zone,bdd_path_xml,config_path,parent) {
        create_menu_new_modif();
        prof classe("Classe");
        noyau()->bdd().get_unique(classe);
        centrale_zone()->open_tab({info_tab_edt::Classe_Tab_Id,classe.id()});
}

void fen_principale_edt::create_menu_new_modif() {}
