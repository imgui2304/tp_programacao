#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

bool UserLogged = false;

void menu(), Servidor();
vector<string> LoadArchive(string path)
{

    fstream archive(path, ios::in);
    vector<string> list;
    string line;
    while (getline(archive, line))
    {
        list.push_back(line);
    }

    archive.close();
    return list;
}

void UserVerificateFunction(string login, string senha, string typeOfUser)
{
    vector<string> Logins, Senhas;

    if (typeOfUser == "user::client")
    {
        Logins = LoadArchive("./arquivos/autenticacao/clientes/login.txt");
        Senhas = LoadArchive("./arquivos/autenticacao/clientes/login.txt");
    }
    else if (typeOfUser == "user::admin")
    {
        Logins = LoadArchive("./arquivos/autenticacao/admins/login.txt");
        Senhas = LoadArchive("./arquivos/autenticacao/admins/senhas.txt");
    }
    else
    {
        cout << "Não foi possível identificar o tipo de usuário..." << endl;
    }

    for (int i = 0; i < Logins.size() && UserLogged == false; i++)
    {

        if (Logins[i] == login && Senhas[i] == senha)
        {

            UserLogged = true;
        }
    }
}

struct Product
{
    string NameOfProduct;
    string PathProduct;
};
void createProduct(string productNew, string priceOfNewProduct, vector<Product> TypesProduct)
{
    fstream Arq;

    Arq.open(TypesProduct[0].PathProduct, ios::app);

    if (Arq)
    {

        Arq << endl
            << productNew << endl;
        Arq
            << priceOfNewProduct << endl;
        cout << "Produto criado com sucesso" << endl;
        Arq.close();

        Servidor();
    }
    else
    {
        cout << "Não foi possível abri o arquivo.";
    }
}
void menuForCreateProduct()
{
    // string TypesProduct[3] = {"Ipads", "Iphones", "Airpods"};
    vector<Product> TypesProduct;
    Product produto1, produto2, produto3;

    produto1.NameOfProduct = "Criar: Ipads";
    produto1.PathProduct = "./arquivos/produtos/ProdutosIpad.txt";
    TypesProduct.push_back(produto1);

    produto2.NameOfProduct = "Criar: Iphones";
    produto2.PathProduct = "./arquivos/produtos/ProdutosAirpods.txt";
    TypesProduct.push_back(produto2);

    produto3.NameOfProduct = "Criar: Airpods";
    produto3.PathProduct = "./arquivos/produtos/ProdutosAirpods.txt";
    TypesProduct.push_back(produto3);

    int operacao = 0;

    cout << "================================================================" << endl;
    cout << left << setw(40) << "CRIADOR DE PRODUTO" << endl;
    cout << "================================================================" << endl;

    cout << left << setw(50) << "Código" << setw(50) << "Criar" << endl;
    for (int i = 0; i < TypesProduct.size(); i++)
    {
        cout << left << setw(50) << i << setw(50) << TypesProduct[i].NameOfProduct << endl;
    }
    cout << "Digite o código do produto que você deseja criar: ";
    cin >> operacao;
    string productNew, priceOfNewProduct;

    if (TypesProduct[operacao].NameOfProduct.find("Ipads") != string::npos)
    {
        cout << "Digite o nome do novo ipad: ";
        fflush(stdin);
        getline(cin, productNew);
        cout << "Digite o preço do novo ipad: ";
        cin >> priceOfNewProduct;

        createProduct(productNew, priceOfNewProduct, TypesProduct);
    }
    else if (TypesProduct[operacao].NameOfProduct.find("Airpods") != string::npos)
    {
        cout << "Digite o nome do novo Airpods: ";
        fflush(stdin);
        getline(cin, productNew);
        cout << "Digite o preço do novo Airpods: ";
        cin >> priceOfNewProduct;

        createProduct(productNew, priceOfNewProduct, TypesProduct);
    }
    else if (TypesProduct[operacao].NameOfProduct.find("Iphones") != string::npos)
    {
        cout << "Digite o nome do novo Iphone: ";
        fflush(stdin);
        getline(cin, productNew);
        cout << "Digite o preço do novo Iphone: ";
        cin >> priceOfNewProduct;

        createProduct(productNew, priceOfNewProduct, TypesProduct);
    }
    else
    {
        cout << "ERRO: Tipo de produto não encontrado.";
    }
}
// Função Servidor
void Servidor()
{
    vector<string> Logins = LoadArchive("./arquivos/autenticacao/admins/login.txt"), Senhas = LoadArchive("./arquivos/autenticacao/admins/senhas.txt");
    string login, senha;

    if (!UserLogged)
    {
        cout << "Digite seu Login: ";
        cin >> login;
        cout << "Digite sua senha: ";
        cin >> senha;
    }
    UserVerificateFunction(login, senha, "user::admin");

    if (!UserLogged)
    {

        cout << ">> Login ou senha incorreto, tente novamente mais tarde." << endl;
    }
    else
    {

        int operacao = 0;

        string Operacoes[1] = {"Criar Produto"};
        cout << left << setw(20) << "Codigo" << setw(20) << "Operação" << endl;
        for (int i = 0; i < 1; i++)
        {
            cout << left << setw(20) << i << setw(20) << Operacoes[i] << endl;
        }
        cout << ">> Digite: ";
        cin >> operacao;
        switch (operacao)
        {
        case 0:
            menuForCreateProduct();
            break;

        default:

            break;
        }
    }
}

void menu()
{
    string Operacoes[2] = {"Servidor", "Cliente"};
    int operacao = 0;
    cout
        << "> Selecione a operação desejada." << endl;
    cout << left << setw(20) << "Codigo" << setw(20) << "Operação" << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << left << setw(20) << i << setw(20) << Operacoes[i] << endl;
    }
    cout << ">> Digite: ";
    cin >> operacao;

    switch (operacao)
    {
    case 0:
        Servidor();
        break;

    default:

        break;
    }
}
int main()
{
    menu();
    // fstream Produtos("./arquivos/produtos/ProdutosIpad.txt");
    // if (!Produtos)
    // {
    //     cerr << "Erro ao abrir o arquivo de produtos." << std::endl;
    //     return 1;
    // }

    // string ProdutosNome[6];
    // float preco[6];
    // int count = 0;
    // string linha;
    // while (getline(Produtos, linha) && count < 6)
    // {
    //     ProdutosNome[count] = linha;
    //     getline(Produtos, linha);
    //     preco[count] = stof(linha);
    //     count++;
    // }

    // Produtos.close();
    // cout << left << setw(50) << "Nome" << setw(50) << "Preço" << endl;

    // for (int i = 0; i < count; i++)
    // {
    //     cout << left << setw(50) << ProdutosNome[i] << setw(50) << preco[i] << endl;
    // }

    return 0;
}