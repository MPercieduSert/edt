/*Auteur: PERCIE DU SERT Maxime
 *Date: 04/06/2022
 */
#ifndef TAB_EDT_H
#define TAB_EDT_H

#include "abstract_tab.h"
#include "bdd_edt.h"
#include "model_tableau_edt.h"
#include "model_tree_edt.h"
#include <QLabel>
#include <QTableView>



namespace edt_mps {
/*! \ingroup groupe_fen_edt
 * \brief Fenêtre à onglet de l'application edt.
 */
class edt_tab : public mps::fenetre::predef_tab {
    Q_OBJECT
public:
    //! Constructeur.
    using predef_tab::predef_tab;

    //! Créateur d'onglet.
    mps::fenetre::abstract_tab_module *create_tab(const tab_index & pair,
                                       const std::vector<QVariant> & args = std::vector<QVariant>()) const override;

    //! Accesseur de la base de donnée.
    bdd_edt & bdd() const noexcept
        {return static_cast<bdd_edt &>(m_bdd);}
};

/*! \ingroup groupe_fen_edt
 * \brief Onglet parent dans edt.
 */
class abstract_edt_tab : public mps::fenetre::abstract_tab_module_with_bdd {
    Q_OBJECT
protected:
    prof m_prof;                                //!< Enseignant de l'onglet.
    mps::vector_ptr<matiere> m_matieres;        //!< Matière de l'enseignant
    QLabel * m_nom_label;                       //!< Label du nom
    QLineEdit * m_nom_edit;                     //!< Edition du Nom
    mps::widget::node_view * m_creneau_view;    //!< Vue des créneaux.
    matiere_creneau_model * m_creneau_model;    //!< Model des créneaux
    QPushButton * m_libre_bouton;               //!< Bouton libre
    QPushButton * m_interdit_bouton;            //!< Bouton interdit
    QHBoxLayout * m_bouton_layout;              //!< Calque des boutons
    QHBoxLayout * m_nom_layout;                 //!< Calque du nom
    QVBoxLayout * m_horaire_layout;             //!< Calque des horaires
    QHBoxLayout * m_main_layout;                //!< Calque principal
public:
    //! Constructeur.
    abstract_edt_tab(bdd_edt & bdd, tab_index pair, QWidget * parent = nullptr);

    void become_current() override
        {emit action_permise(mps::fenetre::Sauver_Action);}

    //! Accesseur de la base de donnée.
    bdd_edt & bdd() const override
        {return static_cast<bdd_edt &>(m_bdd);} 

protected:
    //! Ajoute un bouton
    void add_bouton(QPushButton * bouton, szt indice);
    //! Ajout les boutons
    void add_boutons();
};

/*! \ingroup groupe_fen_edt
 * \brief Onglet de la classe dans edt.
 */
class classe_tab : public abstract_edt_tab {
    Q_OBJECT
protected:
    model_tableau_edt * m_model;
    QTableView * m_view;
public:
    //! Constructeur.
    classe_tab(bdd_edt & bdd, tab_index pair, QWidget * parent = nullptr);

    //! Accesseur de l'identifiant de la matière classe.
    idt id_matiere() const
        {return m_matieres.front().id();}

    //! Accesseur du titre.
    QString title() const override
        {return m_matieres.front().nom();}

    //! Sauvegarde.
    void sauver() override;
};

/*! \ingroup groupe_fen_edt
 * \brief Onglet d'un prof dans edt.
 */
class prof_tab : public abstract_edt_tab {
    Q_OBJECT
protected:

public:
    //! Constructeur.
    prof_tab(bdd_edt & bdd, tab_index pair, QWidget * parent = nullptr);

    //! Accesseur du titre.
    QString title() const override
        {return m_prof.nom();}
};
}

#endif // TAB_EDT_H
