/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Tabelas;

import DAO.DAOUsuario;
import Modelo.Usuario;
import java.util.ArrayList;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author mathe
 */
public class TabelaUsuario extends AbstractTableModel{
    
    static DAOUsuario daoUsuario = new DAOUsuario();
    static ArrayList<Usuario> usuarios;
    String[] colunas = {"Nome", "Sobrenome", "Reg. Acadêmico", "ID"};
    
    public TabelaUsuario(){
        //Marcando o ponteiro de categorias com o ponteiro do vetor de categorias dos dados
        usuarios = (ArrayList<Usuario>) daoUsuario.getLista();
        this.fireTableDataChanged();
    }
    
    public void addUsuario(Usuario usuario){
        daoUsuario.incluir(usuario);
        this.fireTableDataChanged();
    }
    
    public void updateUsuario(Usuario usuarioNovo, Usuario usuarioVelho){
        daoUsuario.atualizar(usuarioVelho, usuarioNovo);
        this.fireTableDataChanged();
    }
    
    public void deletarUsuario(Usuario usuario){
        daoUsuario.remover(usuario);
        this.fireTableDataChanged();
    }
    
    @Override
    public int getRowCount() {
        return usuarios.size();
    }

    @Override
    public int getColumnCount() {
        return colunas.length;
    }
    
    @Override
    public String getColumnName(int column) {
        return colunas[column];
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        return switch (columnIndex){
            case 0 -> usuarios.get(rowIndex).getNome();
            case 1 -> usuarios.get(rowIndex).getSobreNome();
            case 2 -> usuarios.get(rowIndex).getRegAcademico();
            default -> usuarios.get(rowIndex).getId();
        };
    }
    
}
