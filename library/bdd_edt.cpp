#include "bdd_edt.h"

using namespace edt_mps;

bdd_edt::bdd_edt()
    :bdd_predef("QSQLITE",{mps::b2d::bdd_version::Nbr_Version_Predef -1, mps::b2d::bdd_version::Nbr_Version_Bdd_Edt - 1},
               std::make_unique<managers_edt>()) {}

bool bdd_edt::del_v(idt id, entidt id_entity) {
    auto ctr = true;
    // Spécifique
    switch (id_entity) {
    case prof::ID:
        ctr = del_list<matiere>(matiere::Id_Prof,id);
        break;
    case matiere::ID:
        ctr = del_list<horaire>(horaire::Id_Matiere,id)
                && del_list<creneau>(creneau::Id_Matiere,id);
        break;
    case creneau::ID:
        ctr = del_list<horaire>(horaire::Id_Creneau,id);
    }
    return ctr && bdd_predef::del_v(id,id_entity);
}


void bdd_edt::liste_mise_a_jour_bdd(int version, idt type) {
    bdd_predef::liste_mise_a_jour_bdd(version,type);
    if(type == mps::b2d::bdd_version::Edt_Type) {
        switch (version) {
        case mps::b2d::bdd_version::Initiale: {
            creer_table<prof>();
            creer_table<matiere>();
            creer_table<creneau>();
            creer_table<horaire>();
            prof classe("Classe");
            save(classe);
            matiere mat;
            mat.set_id_prof(classe.id());
            mat.set_nom("Nom de la classe?");
            save(mat);
            creneau heure;
            heure.set_id_matiere(mat.id());
            heure.set_num(Num_Nbr_Heure);
            heure.set_code(Nbr_Heure);
            save(heure);
            m_manager->save_version(mps::b2d::bdd_version::Creation,mps::b2d::bdd_version::Edt_Type);
        }
        }
    }
}

