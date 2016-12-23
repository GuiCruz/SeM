#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

typedef vector <double> record_t;
typedef vector <record_t> data_t;
int i=0;

//-----------------------------------------------------------------------------
// Carregando o operador istream para ler uma lista CSV, record é uma lista de
// doubles separados por vírgulas
istream& operator >> ( istream& ins, record_t& record )
  {
  // Limpando qualquer dado que poderia estar armazenado anteriormente
  record.clear();

  // Lendo a linha inteiro como uma string
  string line;
  getline( ins, line );

  // stringstream separa os dados por ,
  stringstream ss( line );
  string field;
  while (getline( ss, field, ',' ))
    {
    // Converte todos os campos em double
    stringstream fs( field );
    double f = 0.0;  // (default value is 0.0)
    fs >> f;

    // adiciona cada valor convertido para o fim do record
    record.push_back( f );
    }

  // retorna o arugmento stream
  return ins;
  }

//----------------------------------------------------------------------------
// Carrega o operador para ler uma lista de CSV records
istream& operator >> ( istream& ins, data_t& data )
  {
  // Limpa qualquer dado armazenado anteriormente
  data.clear();

  // Para cada record que se lê do arquivo, salva em um data.
  record_t record;
  while (ins >> record)
    {
    data.push_back( record );
    }

  // retorna o argumento stream
  return ins;
  }

//-----------------------------------------------------------------------------
// Juntando tudo

void readdata(){
	// Salvando o dados
	data_t data;
	/*
	 * Para ler múltiples arquivos csv on Files/ e além!
	*/
	char fn[32];
	  snprintf (fn, sizeof fn, "files/d_%02d.csv", i);
	  // O arquivo contendo o dado é lido e salvo
	  ifstream infile(fn);
	  infile >> data;

	  // Mostra se houve algum erro
	  if (!infile.eof())
	    {
		cout << fn << "\n";
	    cout << "Error reading the file!\n";
	    }
	  infile.close();

	  // quantos records possui
	  cout << "Your CSV file contains " << data.size() << " records.\n";
	  /* Data format
	   * u50,d50,h,hu,ps,p,g,v,s,hl,uf,t,y,r,mill,o,ucr,tcr,ycr,qt,
	   *996479419
	   * Cálculo das equações citadas,
	   */
	  double ks = 0.354;
	  double zo = 0.033*ks;
	  double ucf = (data[0][0]*0.4)/(log(data[0][3]/zo));
	  double s = (((data[0][4])-(data[0][5])) / (data[0][5]))*data[0][6];
	  double ya = ((s*(pow(data[0][1] , 3.0)))/ ((data[0][5])*(pow(data[0][7], 2.0))));
	  double re = ((ucf*data[0][1])/(data[0][7]));
	  double o = pow(((pow(ya, 0.5))/re), 2.0);
	  double ucr = pow(  (o*(s*(data[0][1]))), 0.5);
	  double tcf = (data[0][5])*(pow(ucf, 2.0));
	  double tcr = (data[0][5])*(pow(ucr, 2.0));
	  double a = tcf/((s*(data[0][5]))*(data[0][1]));
	  double ac = tcr/((s*(data[0][5]))*(data[0][1]));
	  double qt = (8*(data[0][1]*(pow((s*data[0][1]), 0.5))))*(pow((a-ac),0.5));




	  cout << ucf << "\n";
	  cout << ya << "\n";
	  cout << re << "\n";
	  cout << o << "\n";
	  cout << ucr << "\n";
	  cout << tcf << "\n";
	  cout << tcr << "\n";
	  cout << a << "\n";
	  cout << ac << "\n";
	  cout << qt << "\n";
	  //Para ler tudo.
	  i++;
}

int main()
  {

	readdata();
  return 0;
  }
