/*Auteur: PERCIE DU SERT Maxime
 *Date: 05/06/2021
 */
#ifndef MODEL_TREE_EDT_H
#define MODEL_TREE_EDT_H

#include "bdd_edt.h"
#include "item_node_model.h"

namespace edt_mps {

/*! \ingroup groupe_gui_edt
 * \brief Base de donnée des matières et des créneaux.
 */
class matiere_creneau_model : public mps::model_base::item_node_bdd_model {
    Q_OBJECT
protected:
    const idt m_prof_id;          //!< Identifiant de l'enseigant.
public :
    //! Constructeur.
    matiere_creneau_model(idt id_prof, bdd_edt & bd, QObject *parent = nullptr);

    //! Accesseur de la base de donnée.
    bdd_edt & bdd() const
        {return static_cast<bdd_edt &>(m_bdd);}
    
    //! Insert count noeuds de nature type avant la position pos de parent.
    std::list<node_iter> insert(const node_index &parent, numt pos, numt count, int type = Default_Type) override;

    //! Mutateur des données du model.
    bool set(const node_index &index, const QVariant &value, int role) override;

protected:
    //! Fabrique des noeuds.
    mps::model_base::node_ptr node_factory(const mps::model_base::node_index & parent, numt pos, int type) override;
};

//! Type de node d'exercice.
enum type_node {
    Creneau_Node,
    Matiere_Node,
    Titre_Node};

//! Cible des données du model.
enum data_cible {
    Classe_Cible,
    Heure_Cible,
    Matiere_Cible,
    Semaine_Cible,
    Titre_Cible};

/*! \ingroup groupe_gui_edt
 * \brief Noeud des models matiere.
 */
class cm_root_node : public mps::model_base::item_bdd_node {
public:
    //! Constructeur.
    using item_bdd_node::item_bdd_node;

    //! Accesseur des données du noeud.
    QVariant data(int cible, int role, numt num = 0) const override;
};

/*! \ingroup groupe_gui_edt
 * \brief Template des noeud des models matiere et creneau.
 */
template<class T> class cm_node_temp : public mps::model_base::item_bdd_node {
protected:
    matiere_creneau_model *m_model;         //!< Pointeur sur le model contenant le noeud.
    T m_ent;                                //!< Entité associé au noeud.
public:
    //! Constructeur.
    cm_node_temp(matiere_creneau_model *model, idt id_ent = 0, int type = Matiere_Node)
        : item_bdd_node(type), m_model(model), m_ent(id_ent) {
        if(m_ent.id())
            model->bdd().get(m_ent);
    }

    //! Accesseur des données du noeud.
    QVariant data(int cible, int role, numt num = 0) const override;

//    //! Accesseur des drapeaux associés à column.
//    flag flags(int cible, numt num = 0) const override;

    //! Accesseur de l'identifiant
    idt id() const
        {return m_ent.id();}

    //! Enregistre les données du noeud.
    void insert(mps::b2d::bdd &bdd) override {
        if(!m_iter.root()) {
            m_ent.set_id_1(static_cast<const cm_node_temp<T> &>(**m_iter.parent()).id());
            m_ent.set_num(static_cast<int>(m_iter.position()));
            bdd.save(m_ent);
        }
    }

    //! Enregistre les données du noeud.
    void save(mps::b2d::bdd &bdd) override{
        if(m_ent.id())
            bdd.save(m_ent);
    }
//    //! Mutateur des données du noeud.
//    flag set_data(int cible, const QVariant & value, int role, numt num = 0) override;
};



/*! \ingroup groupe_gui_edt
 * \brief Noeud des models matiere.
 */
class matiere_node : public cm_node_temp<matiere> {
public:
    //! Constructeur.
    using cm_node_temp::cm_node_temp;

    //! Accesseur des données du noeud.
    QVariant data(int cible, int role, numt num = 0) const override;

    //! Accesseur des drapeaux associés à column.
    flag flags(int cible, numt num = 0) const override;

    //! Mutateur des données du noeud.
    flag set_data(int cible, const QVariant & value, int role, numt num = 0) override;
};

/*! \ingroup groupe_gui_edt
 * \brief Noeud des models creneau.
 */
class creneau_node : public cm_node_temp<creneau> {
public:
    //! Constructeur.
    using cm_node_temp::cm_node_temp;

    //! Accesseur des données du noeud.
    QVariant data(int cible, int role, numt num = 0) const override;

    //! Accesseur des drapeaux associés à column.
    flag flags(int cible, numt num = 0) const override;

    //! Mutateur des données du noeud.
    flag set_data(int cible, const QVariant & value, int role, numt num = 0) override;
};

//////////////////////////////////////////// Template méthode /////////////////////////////////////////////////
template<class T> QVariant cm_node_temp<T>::data(int cible, int role, numt num) const {
    if(cible == mps::model_base::Node_Cible && num == mps::model_base::Node_Num && role == mps::model_base::Id_Role)
        return m_ent.id();
    return item_bdd_node::data(cible, role, num);
}
}

#endif // MODEL_TREE_EDT_H
