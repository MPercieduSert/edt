/*Auteur: PERCIE DU SERT Maxime
 *Date: 05/06/2021
 */
#ifndef WIDGET_EDT_H
#define WIDGET_EDT_H

#include "enum_edt.h"
#include <QCheckBox>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QWidget>
#include "type_mps.h"

namespace edt_mps {
/*! \ingroup groupe_gui_edt
 * \brief Widget creneau.
 */
class creneau_widget : public QWidget {
    Q_OBJECT
protected:
    QCheckBox * m_classe;               //!< Option de demie-classe.
    QCheckBox * m_semaine;              //!< Option d'une semaine sur deux.
    QLabel * m_heure_label;             //!< Label du nombre d'heures.
    QSpinBox * m_heure_spin_box;        //!< Choix du nombre d'heures.
    QHBoxLayout * m_main_Layout;        //!< Calque principal.
public:
    //! Constructeur.
    creneau_widget(QWidget * parent = nullptr);

    //! Mutateur de la valeur.
    void set_value(mps::flag code);

    //! Accesseur de la valeur.
    mps::flag value() const;
};

/*! \ingroup groupe_gui_edt
 * \brief Widget creneau.
 */
class matiere_creneau_widget : public creneau_widget {
    Q_OBJECT
protected:
    QLabel * m_matiere_label;             //!< Label de la matiere.
    QLineEdit * m_matiere_edit;           //!< Nom de la matiere.
    QHBoxLayout * m_matiere_layout;       //!< Calque de la matiere.
    QVBoxLayout * m_main_layout;          //!< Calque principale.
public:
    //! Constructeur.
    matiere_creneau_widget(QWidget * parent = nullptr);
};

}
#endif // WIDGET_EDT_H
