/*Auteur: PERCIE DU SERT Maxime
 *Date: 20/08/2019
 */
#ifndef MANAGERS_EDT_H
#define MANAGERS_EDT_H

#include "entity_edt.h"
#include "gestion_restriction_cible.h"
#include "managers_predef.h"

namespace edt_mps {
/*! \ingroup groupe_manager_edt
 * \brief Managers de l'application edt.
 */
class managers_edt: public mps::manager::managers_predef {

public:
    //! Constructeur.
    managers_edt();

    //! Destructeur.
    ~managers_edt() = default;
};
}
#endif // MANAGERS_EDT_H
