/*Auteur: PERCIE DU SERT Maxime
 *Date: 05/06/2022
 */
#ifndef MODEL_TABLEAU_EDT_H
#define MODEL_TABLEAU_EDT_H

#include "bdd_edt.h"
#include <QAbstractTableModel>

namespace edt_mps {

/*! \ingroup groupe_gui_edt
 * \brief Base de donnée de l'application edt.
 */
class model_tableau_edt : public QAbstractTableModel {
    Q_OBJECT
protected:
    bdd_edt & m_bdd;                            //!< Base de donnée.
    const idt m_id_matiere;                     //!< Id matiere.
    const int m_premiere_heure = 8;             //!< Première heure.
    const int m_nbr_heure;                      //!< Nombre d'heure.
    const QStringList m_header = {tr("Lundi"),tr("Mardi"),tr("Mercredi"),tr("Jeudi"),tr("Vendredi"),tr("Samedi")};   //!< Entête.
    mps::vector_ptr<horaire> m_horaire;         //!< Données horraire.

public:
    enum {Nbr_Jour = 6};
    enum option_case_enum {Libre,Interdit,Nbr_Option_Case};
    //! Structure d'option
    struct option_case{
        QString text;
        QColor color;
    };
    static const std::array<const option_case,Nbr_Option_Case> options; //!< Option des cases

    //! Constructeur.
    model_tableau_edt(bdd_edt & bdd, idt id_matiere, int nbr_heure, QObject * parent = nullptr);

    //! Nombre de colonne.
    int columnCount(const QModelIndex & parent = QModelIndex()) const override
        {return parent.isValid() ? 0 : Nbr_Jour;}

    //! Accesseur des donnée.
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //! Accesseur des en tête de lignes et colonnes.
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    //! Conversion de l'index en indice.
    szt indice(const QModelIndex & index) const noexcept
        {return static_cast<szt>(index.column() * m_nbr_heure + index.row());}


    //! Nombre de ligne.
    int rowCount(const QModelIndex & parent = QModelIndex()) const override
        {return parent.isValid() ? 0 : m_nbr_heure;}

    //! Change la veleur de la selection.
    void change_value_selection(QItemSelectionModel * selection, flag code, idt id = 0);

    //! Sauvegarde le model.
    void sauver();
};
}
#endif // MODEL_TABLEAU_EDT_H
