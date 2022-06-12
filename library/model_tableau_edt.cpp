#include "model_tableau_edt.h"

using namespace edt_mps;

const std::array<const model_tableau_edt::option_case,model_tableau_edt::Nbr_Option_Case> model_tableau_edt::options = {
    model_tableau_edt::option_case{tr("Libre"),QColor("green")},
    model_tableau_edt::option_case{tr("Interdit"),QColor("red")}};

model_tableau_edt::model_tableau_edt(bdd_edt & bdd, idt id_matiere, int nbr_heure, QObject * parent)
    : QAbstractTableModel(parent), m_bdd(bdd), m_id_matiere(id_matiere), m_nbr_heure(nbr_heure) {
    m_horaire = m_bdd.get_list<horaire>(horaire::Id_Matiere,m_id_matiere,horaire::Num);
    if(m_horaire.size() < static_cast<szt>(m_nbr_heure) * Nbr_Jour - 1) {
        for (szt i = m_horaire.size(); i !=  static_cast<szt>(m_nbr_heure) * Nbr_Jour; ++i)
            m_horaire.push_back(horaire(m_id_matiere,static_cast<int>(i),Libre_Code));
    }
}

void model_tableau_edt::change_value_selection(QItemSelectionModel * selection, flag code, idt id){
    auto list_index = selection->selectedIndexes();
    for (auto i = list_index.cbegin(); i != list_index.cend(); ++i) {
        m_horaire[indice(*i)].set_code(code);
        m_horaire[indice(*i)].set_id_creneau(id);
        dataChanged(*i,*i);
    }
}

QVariant model_tableau_edt::data(const QModelIndex &index, int role) const {
    szt option = m_horaire.at(indice(index)).code() & Libre_Code ?
                Libre : Interdit;
    switch (role) {
    case Qt::DisplayRole:
        return options.at(option).text;
    case Qt::DecorationRole:
        return options.at(option).color;
    }
    return QVariant();
}

QVariant model_tableau_edt::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal)
            return m_header[section];
        return QString::number(section+m_premiere_heure).append("h à ")
                .append(QString::number(section + m_premiere_heure + 1)).append("h");
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}

void model_tableau_edt::sauver() {
    m_bdd.save(m_horaire);
}
