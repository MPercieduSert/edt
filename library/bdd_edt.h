/*Auteur: PERCIE DU SERT Maxime
 *Date: 02/06/2022
 */
#ifndef BDD_EDT_H
#define BDD_EDT_H

#include "managers_edt.h"
#include "bdd_predef.h"

namespace edt_mps {
/*! \ingroup groupe_manager_edt
 * \brief Base de donnée de l'application edt.
 */
class bdd_edt : public mps::b2d::bdd_predef {
public:
    //! Constructeurs hérités.
    using bdd_predef::bdd_predef;

    //Constructeur.
    bdd_edt();

    //! Destructeur. Referme la base de donnée.
    ~bdd_edt() override = default;

protected:
    //! Supprime l'entité d'identifiant id de type d'identifiant id_entity de la base de données.
    bool del_v(idt id, entidt id_entity) override;

    //! Mise à jour de la base de donnée.
    void liste_mise_a_jour_bdd(int version, idt type) override;
};
}

#endif // BDD_EDT_H
