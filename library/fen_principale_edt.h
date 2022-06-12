/*Auteur: PERCIE DU SERT Maxime
 *Date: 02/06/2022
 */
#ifndef FEN_PRINCIPALE_EDT_H
#define FEN_PRINCIPALE_EDT_H

#include "noyau_edt.h"
#include "predef_fen_principale.h"
#include "edt_tab.h"

namespace edt_mps {
/*! \ingroup groupe_fen_edt
 * \brief Fenêtre principale de l'application edt.
 *
 * Fenêtre principale de l'application edt:
 *  + Crée les différents menus.
 *
 */
class fen_principale_edt : public mps::fenetre::predef_fen_principale {
    Q_OBJECT
protected:

public:
    //! Constructeur.
    fen_principale_edt(noyau_edt * noyau,
                      std::unique_ptr<bdd_edt>  bdd,
                      mps::fenetre::predef_zone_centrale * central_zone,
                      const QString &bdd_path_xml = DATA_BASE,
                      const QString & config_path = QDir::currentPath().append("/Config.xml"),
                      QWidget *parent = nullptr);

    //! Destructeur.
    ~fen_principale_edt() override = default;

    //! Création du sous-menu nouvau.
    void create_menu_new_modif();

    //! Acceseur du noyau.
    noyau_edt * noyau() override
        {return static_cast<noyau_edt *>(m_noyau);}
};
}
#endif // FEN_PRINCIPALE_EDT_H
