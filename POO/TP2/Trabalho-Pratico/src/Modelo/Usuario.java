package Modelo;

public class Usuario extends Pessoa{
    private int regAcademico;

    public Usuario(int regAcademico, int id, String nome, String sobreNome) {
        super(id, nome, sobreNome);
        this.regAcademico = regAcademico;
    }
    
    public Usuario(int regAcademico, String nome, String sobreNome){
        super(nome, sobreNome);
        this.regAcademico = regAcademico;
    }

    public int getRegAcademico() {
        return regAcademico;
    }

    public void setRegAcademico(int regAcademico) {
        this.regAcademico = regAcademico;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Usuario other = (Usuario) obj;
        return super.equals(other) && this.regAcademico == other.regAcademico;
    }
    
    
}