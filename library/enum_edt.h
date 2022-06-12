/*Auteur: PERCIE DU SERT Maxime
 *Date: 02/06/2022
 */
#ifndef ENUM_MANAGER_EDT_H
#define ENUM_MANAGER_EDT_H

#include "bdd_predef.h"
#include "predef_tab.h"

namespace mps {
namespace b2d {
    namespace bdd_version {
        //! Version de la base de données.
        enum version_bdd_edt{Nbr_Version_Bdd_Edt = Nbr_Version};
        //! Type de mise à jour.
        enum type_bdd_edt{Edt_Type = Nbr_Type, Nbr_Type_Edt};
    }

    namespace cible_id {
        //! Numéro de cible des entités de Note non prédéfinies.
        enum EntityEdt {Creneau = cible_id::Nbr_Cible_Predef,
                        Horaire,
                        Matiere,
                        Prof,
                        Nbr_Cible};
}
}}

namespace edt_mps {
    //! Numero de programmation de creneau.
    enum num_configuration {Num_Nbr_Heure};

    //! Code pour les créneau
    enum creneau_code : mps::flag::flag_type {Heure_Creneau = 0x1F,
                                             Classe_Creneau = Heure_Creneau,
                                             Semaine_Creneau = Classe_Creneau * 2};

    //! Code pour les horaires
    enum horaire_code : mps::flag::flag_type {Interdit_Code = 0, Libre_Code = 0x1};


    namespace info_entity_edt {
        //! Liste des identifiants des entités
        enum entity_id{Creneau = mps::info_entity::Nbr_Entity_Predef,
                       Horaire,
                       Matiere,
                       Prof,
                       Nbr_Entity_Edt};
    }

    namespace info_tab_edt {
    enum tab_id {Classe_Tab_Id = mps::fenetre::predef_tab::Nbr_Predef_Tab_Id,
                    Prof_Tab_Id,
                    };
    }

    //! Valeur par defaut.
    enum default_values {Nbr_Heure = 10, Min_Heure = 1};
}



#endif // ENUM_MANAGER_EDT_H
