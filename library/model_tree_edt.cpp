#include "model_tree_edt.h"

using namespace mps::model_base;
using namespace edt_mps;

matiere_creneau_model::matiere_creneau_model(idt id_prof, bdd_edt & bd, QObject *parent)
    : item_node_bdd_model(bd,parent), m_prof_id(id_prof) {
    insert_nodes(node_index(),0,1);
}

std::list<node_iter> matiere_creneau_model::insert(const node_index &parent, numt pos, numt count, int type) {
    std::list<node_iter> nodes;
    if(parent.is_valid() && pos <= parent.child_count()) {
        begin_insert_nodes(parent,pos,count);
            nodes = m_data.insert_nodes(parent,pos,count,
                               [this,type](const node_index &parentArg, numt posArg){return node_factory(parentArg,posArg,type);});
        end_insert_nodes();
    }
    else if(pos == 0 && count == 1){
        begin_reset_model();
            m_data.set_root(std::make_unique<cm_root_node>(Titre_Node));
            auto liste_matiere = bdd().get_list_id<matiere>(matiere::Id_Prof,m_prof_id,matiere::Num);
            liste_matiere.pop_front();
            auto root_index = index(node_index(),0);
            for (auto it_matiere_id = liste_matiere.cbegin(); it_matiere_id != liste_matiere.cend(); ++it_matiere_id) {
                auto node_it = m_data.push_back(root_index,std::make_unique<matiere_node>(this,*it_matiere_id));
                auto liste_creneau = bdd().get_list_id<creneau>(creneau::Id_Matiere, *it_matiere_id,creneau::Num);
                for(auto it_creneau_id = liste_creneau.cbegin(); it_creneau_id != liste_creneau.cend(); ++it_creneau_id)
                    m_data.push_back(node_it,std::make_unique<creneau_node>(this,*it_creneau_id));
            }
        end_reset_model();
    }
    return nodes;
}

mps::model_base::node_ptr matiere_creneau_model::node_factory(const mps::model_base::node_index & parent,
                                                            numt /*pos*/, int /*type*/) {
    if(parent.is_root())
        return std::make_unique<matiere_node>(this);
    else
        return std::make_unique<creneau_node>(this);
}

bool matiere_creneau_model::set(const node_index &index, const QVariant &value, int role) {
    if(check_index(index)){
        auto changeRole = m_data.get_node(index).set_data(index.cible(),value,role,index.num());
        if(changeRole){
            emit data_changed(index,changeRole);
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////// cm_root_node ////////////////////////////////////////////////////
QVariant cm_root_node::data(int cible, int role, numt num) const {
    switch (cible) {
    case Titre_Cible:
        switch (role) {
        case Label_Role:
            return "Liste des matières à créneau horaire fixe :";
        case Type_Role:
            return Label_Sub_Node;
        }
        break;
    case mps::model_base::Node_Cible:
        if(num == Node_Num && role == Cibles_Role)
                return QVariantList({Titre_Cible});
    }
    return item_bdd_node::data(cible, role, num);
}

//////////////////////////////////////////// matiere_node ////////////////////////////////////////////////////
QVariant matiere_node::data(int cible, int role, numt num) const {
    switch (cible) {
    case Matiere_Cible:
        switch (role) {
        case Label_Role:
            return "Matiere :";
        case Orientation_Role:
            return Qt::Horizontal;
        case Type_Role:
            return Line_Edit_Sub_Node;
        case String_Role:
            return m_ent.nom();
        }
        break;
    case mps::model_base::Node_Cible:
        if(num == Node_Num && role == Cibles_Role)
                return QVariantList({Matiere_Cible});
    }
    return item_bdd_node::data(cible, role, num);
}

flag matiere_node::flags(int cible, numt num) const {
    if(cible == Node_Cible && m_iter.root())
        return No_Flag_Node;
    return cm_node_temp<matiere>::flags(cible,num);
}

flag matiere_node::set_data(int cible, const QVariant & value, int role, numt num) {
    if(cible == Matiere_Cible && role == String_Role){
        m_ent.set_nom(value.toString());
        return Main_Same_Change_Flag;
    }
    return cm_node_temp<matiere>::set_data(cible, value, role, num);
}
////////////////////////////////////////////////// Creneau Node ///////////////////////////////////////////
QVariant creneau_node::data(int cible, int role, numt num) const {
    switch (cible) {
    case Classe_Cible:
        switch (role) {
        case Label_Role:
            return "Demi-Classe :";
        case Orientation_Role:
            return Qt::Horizontal;
        case Type_Role:
            return Check_Sub_Node;
        case Check_State_Role:
            return static_cast<bool>(m_ent.code() & Classe_Creneau);
        }
        break;
    case Semaine_Cible:
        switch (role) {
        case Label_Role:
            return "Une semaine sur deux :";
        case Orientation_Role:
            return Qt::Horizontal;
        case Type_Role:
            return Check_Sub_Node;
        case Check_State_Role:
            return static_cast<bool>(m_ent.code() & Classe_Creneau);
        }
        break;
    case Heure_Cible:
        switch (role) {
        case Orientation_Role:
            return Qt::Horizontal;
        case Label_Role:
            return "Nombre d'heures :";
        case Type_Role:
            return Spin_Box_Sub_Node;
        case Min_role:
            return Min_Heure;
        case Max_role:
            return Nbr_Heure;
        case Int_Role:
            return static_cast<int>(m_ent.code() & Heure_Creneau);
        }
        break;
    case mps::model_base::Node_Cible:
        if(num == Node_Num) {
            switch (role) {
            case Cibles_Role:
                return QVariantList({Heure_Cible,Semaine_Cible,Classe_Cible});
            case Orientation_Role:
                return Qt::Vertical;
            }
        }
        break;
    }
    return cm_node_temp<creneau>::data(cible, role, num);
}

flag creneau_node::flags(int cible, numt num) const {
    if(cible == Node_Cible) {
        if(m_iter.root())
            return No_Flag_Node;
        else
            return cm_node_temp<creneau>::flags(cible,num) & (~Elder_Enable_Flag_Node);
    }
    return cm_node_temp<creneau>::flags(cible,num);
}

flag creneau_node::set_data(int cible, const QVariant & value, int role, numt num) {
    switch (cible) {
    case Classe_Cible:
        if(role == Bool_Role){
            auto code = m_ent.code();
            code.set_value(Classe_Creneau,value.toBool());
            m_ent.set_code(code);
            return Main_Same_Change_Flag;
        }
        break;
    case Semaine_Cible:
        if(role == Bool_Role){
            auto code = m_ent.code();
            code.set_value(Semaine_Creneau,value.toBool());
            m_ent.set_code(code);
            return Main_Same_Change_Flag;
        }
        break;
    case Heure_Cible:
        if(role == Int_Role) {
            auto code = m_ent.code();
            m_ent.set_code((code | ~Heure_Creneau) | value.toUInt());
            return Main_Same_Change_Flag;
        }
        break;
    }
    return cm_node_temp<creneau>::set_data(cible, value, role, num);
}
