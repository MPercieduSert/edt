/*Auteur: PERCIE DU SERT Maxime
 *Date: 02/06/2021
 */
#ifndef NOYAU_EDT_H
#define NOYAU_EDT_H

#include "abstract_noyau.h"
#include "bdd_edt.h"
#include "config_edt.h"


/*! \defgroup groupe_fen_edt Fenêtre note
 * \brief Ensemble des fenêtre et du noyau de l'application edt.
 */

namespace edt_mps {
/*! \ingroup groupe_fen_edt
 * \brief Noyau de l'application edt.
 *
 * Noyau de l'application edt:
 *
 */
class noyau_edt: public mps::fenetre::abstract_noyau {
    Q_OBJECT

public:
    //! Constructeur.
    noyau_edt() {}

    //! Destructeur.
    ~noyau_edt() override = default;

    //! Accesseur de la base de donnée.
    bdd_edt &bdd() override
        {return static_cast<bdd_edt &>(abstract_noyau::bdd());}

    //!Ouvre le gestionnaire de configuration au chemin indiquer.
    void set_config_by_path(const QString & config_path, QWidget *modal_parent = nullptr) override;
};
}
#endif // NOYAU_EDT_H
