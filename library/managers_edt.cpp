#include "managers_edt.h"

using namespace edt_mps;
using namespace mps::b2d;
using namespace mps::manager;

managers_edt::managers_edt()
    : managers_predef (info_entity_edt::Nbr_Entity_Edt,cible_id::Nbr_Cible,"edt_version") {
    //prof
    using unique_prof = nom_unique_sql<prof>;
    info_bdd info_prof("prof","prof",prof::Nbr_Att,{unique_prof::Nbr_Unique});
    info_prof.set_attribut(prof::Nom,"nom",type_attribut_bdd::Text);
    info_prof.set_unique(prof::Nom,unique_prof::Nom_Unique);
    set_manager<prof>(std::make_unique<manager_sql<prof>>(info_prof,std::make_unique<unique_prof>()));
    set_cible<prof>(cible_id::Prof);

    //matiere
    using unique_matiere = id_num_unique_sql<matiere>;
    info_bdd info_matiere("matiere","matiere",matiere::Nbr_Att,{unique_matiere::Nbr_Unique});
    info_matiere.set_attribut(matiere::Id_Prof,"id_prof");
    info_matiere.set_attribut(matiere::Nom,"nm",type_attribut_bdd::Text);
    info_matiere.set_attribut(matiere::Num,"num");
    info_matiere.set_unique(matiere::Id_Prof,unique_matiere::Id_1_Unique);
    info_matiere.set_unique(matiere::Num,unique_matiere::Num_Unique);
    info_matiere.set_foreign_key(matiere::Id_Prof,info_prof);
    set_manager<matiere>(std::make_unique<manager_sql<matiere>>(info_matiere,std::make_unique<unique_matiere>()));
    set_cible<matiere>(cible_id::Matiere);

    //Creneau
    using unique_creneau = id_num_unique_sql<creneau>;
    info_bdd info_creneau("creneau","creneau",creneau::Nbr_Att,{unique_creneau::Nbr_Unique});
    info_creneau.set_attribut(creneau::Id_Matiere,"id_mat");
    info_creneau.set_attribut(creneau::Num,"num");
    info_creneau.set_attribut(creneau::Code,"code");
    info_creneau.set_unique(creneau::Id_Matiere,unique_creneau::Id_1_Unique);
    info_creneau.set_unique(creneau::Num,unique_creneau::Num_Unique);
    info_creneau.set_foreign_key(creneau::Id_Matiere,info_matiere);
    set_manager<creneau>(std::make_unique<manager_sql<creneau>>(info_creneau,std::make_unique<unique_creneau>()));
    set_cible<creneau>(cible_id::Creneau);

    //Horaire
    using unique_horaire = id_num_unique_sql<horaire>;
    info_bdd info_horaire("horaire","horaire",horaire::Nbr_Att,{unique_horaire::Nbr_Unique});
    info_horaire.set_attribut(horaire::Id_Matiere,"id_mat");
    info_horaire.set_attribut(horaire::Id_Creneau,"id_creneau",type_attribut_bdd::Integer,false);
    info_horaire.set_attribut(horaire::Num,"num");
    info_horaire.set_attribut(horaire::Code,"cd");
    info_horaire.set_unique(horaire::Id_Matiere,unique_horaire::Id_1_Unique);
    info_horaire.set_unique(horaire::Num,unique_horaire::Num_Unique);
    info_horaire.set_foreign_key(horaire::Id_Matiere,info_matiere);
    info_horaire.set_foreign_key(horaire::Id_Creneau,info_creneau);
    set_manager<horaire>(std::make_unique<manager_sql<horaire>>(info_horaire,std::make_unique<unique_horaire>()));
    set_cible<horaire>(cible_id::Horaire);
}
