/*Auteur: PERCIE DU SERT Maxime
 *Date: 02/06/2022
 */
#ifndef ENTITY_EDT_H
#define ENTITY_EDT_H

#include "entity_predef.h"
#include "enum_edt.h"

/*! \defgroup groupe_manager_edt Entités et base de données de edt
 * \brief Ensemble des entités, managers et base de données de l'application edt.
 */

/*! \ingroup groupe_manager_edt
 * \brief Espace de noms de l'application note.
 */
namespace edt_mps {
// Type prédéfinies
using entidt = mps::entidt;
using enumt = mps::enumt;
using flag = mps::flag;
using idt = mps::idt;
using numt = mps::numt;
using post = mps::post;
using szt = mps::szt;

ID1_ENTITY(creneau,id_num_code,info_entity_edt::Creneau,Matiere,matiere)
ID1_ENTITY(matiere,id_num_nom,info_entity_edt::Matiere,Prof,prof)
//RELATION_ENTITY(horaire,relation_num_code,info_entity_edt::Horaire,Matiere,matiere,Creneau,creneau)
using prof = mps::entities_base::nom_entity<info_entity_edt::Prof>;

/*! \ingroup groupe_manager_edt
 * \brief Représentation de l'entité annee.
 */
class horaire : public mps::entities::entity_ids<info_entity_edt::Horaire,mps::attribut::id_1_attribut,
                                                                        mps::attribut::id_2_null_attribut,
                                                                        mps::attribut::num_attribut,
                                                                        mps::attribut::code_attribut> {
protected:
    template<class T> using position_enum = mps::entities::position_enum<T,horaire>;
public:
using eaid = mps::entities::entity_ids<info_entity_edt::Horaire,mps::attribut::id_1_attribut,
                                                                mps::attribut::id_2_null_attribut,
                                                                mps::attribut::num_attribut,
                                                                mps::attribut::code_attribut>;

    //! positions des attributs.
    enum position {Id = position_enum<id_attribut>::Position,
                   Id_1 = position_enum<id_1_attribut>::Position,
                   Id_2 = position_enum<id_2_null_attribut>::Position,
                   Num = position_enum<num_attribut>::Position,
                   Code = position_enum<code_attribut>::Position,
                   Nbr_Att = eaid::Nbr_Att,
                   Id_Matiere = Id_1,
                   Id_Creneau = Id_2
                  };

    using eaid::entity_id;
    BASE_ENTITY(horaire)
    ALIAS_CLE(matiere,1)
    ALIAS_CLE(creneau,2)

    //! Constructeur à partir d'un jeux de valeurs attributs unique.
    horaire(idt id_matiere, int num)
        : eaid(0) {
        set_id_matiere(id_matiere);
        set_num(num);}

    //! Constructeur à partir des valeurs attributs.
    horaire(idt id_matiere, int num, flag code, idt id_creneau = 0, idt id = 0)
        : eaid(id) {
        set_id_matiere(id_matiere);
        set_id_creneau(id_creneau);
        set_num(num);
        set_code(code);}
};
}

#endif // ENTITY_EDT_H
