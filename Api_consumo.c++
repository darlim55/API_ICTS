#include <iostream>
#include <curl/curl.h>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

string opcoes(int tipo, int id = 0, string dispositivo = "")
{

  string path;
  if (tipo == 1)
  {
    path = "http://127.0.0.1:3000/sensor";
  }
  else if (tipo == 2)
  {
    path = "http://127.0.0.1:3000/sensor/" + to_string(id);
  }

  else if (tipo == 3)
  {
    path = "http://127.0.0.1:3000/sensor_update/" + to_string(id);
  }
  else if (tipo == 4)
  {

    path = "http://127.0.0.1:3000/sensor_update_disposicao/" + to_string(id);
  }

  return path;
}

void listar_sensores(int tipo, string T = "", int id = 0)
{
  CURL *curl;
  CURLcode res;
  json j = {};
  int http_code;
  std::string readBuffer;
  std::string body = "{ \"tipo\": \"" + T + "\" }";
  std::string path_full = opcoes(tipo, id);
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if (curl)
  {

    // Faz a consulta no banco do tipo de sensor selecionado temperatura ou consumo
    curl_easy_setopt(curl, CURLOPT_URL, path_full.c_str());
    struct curl_slist *hs = NULL;
    hs = curl_slist_append(hs, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());
    curl_easy_setopt(curl, CURLOPT_POST, 1);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    curl_easy_cleanup(curl);
    // Lista os sensores encontrados no banco de dados

    if (http_code != 500)
    {
      if (T == "T")
        cout
            << "Sensores de temperatura" << endl;
      else
        cout << "Sensores de Consumo" << endl;

      json j_complete = nlohmann::json::parse(readBuffer);

      if (tipo == 1)
      {
        for (json its : j_complete)
        {
          for (json::iterator it = its.begin(); it != its.end(); ++it)
          {
            if (it.key() == "_id")
              std::cout << "id"
                        << " : " << it.value() << "\n";
            else
              std::cout << it.key() << " : " << it.value() << "\n";
          }
          std::cout << std::endl;
        }
      }
      else if (tipo == 2)
      {
        for (json::iterator it = j_complete.begin(); it != j_complete.end(); ++it)
        {
          if (it.key() == "_id")
            std::cout << "id"
                      << " : " << it.value() << "\n";
          else
            std::cout << it.key() << " : " << it.value() << "\n";
        }
        std::cout << std::endl;
      }
    }
    else
    {
      cout << readBuffer << endl;
      cout << endl;
    }
  }
}

void listar_sensores_maior_cosumo(int tipo, string T = "", int id = 0)
{
  CURL *curl;
  CURLcode res;
  json j = {};
  float aux = 0;
  std::string readBuffer;
  std::string body = "{ \"tipo\": \"" + T + "\" }";
  std::string path_full = opcoes(1, 1);
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if (curl)
  {

    // Faz a consulta no banco do tipo de sensor selecionado temperatura ou consumo
    curl_easy_setopt(curl, CURLOPT_URL, path_full.c_str());

    struct curl_slist *hs = NULL;
    hs = curl_slist_append(hs, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());
    curl_easy_setopt(curl, CURLOPT_POST, 1);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    json j_complete = nlohmann::json::parse(readBuffer);
    json aux2;
    for (json its : j_complete)
    {
      for (json::iterator it = its.begin(); it != its.end(); ++it)
      {

        if (it.key() == "consumo")
          if (it.value() > aux)
          {
            aux = it.value();
            aux2 = its;
          }
      }
    }

    cout << "Sensor que mais consome energia: " << endl;
    cout << endl;
    for (json::iterator it = aux2.begin(); it != aux2.end(); ++it)
    {

      if (it.key() == "_id")
        std::cout << "id"
                  << " : " << it.value() << "\n";
      else
        std::cout << it.key() << " : " << it.value() << "\n";
    }

    cout << endl;
  }
}

void altera_nome(int tipo, string nome, int id = 0)
{

  CURL *curl;
  CURLcode res;
  json j = {};
  std::string readBuffer;
  std::string body = "{ \"nome\": \"" + nome + "\" }";
  std::string path_full = opcoes(tipo, id);
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if (curl)
  {

    // Faz a consulta no banco do tipo de sensor selecionado temperatura ou consumo
    curl_easy_setopt(curl, CURLOPT_URL, path_full.c_str());
    struct curl_slist *hs = NULL;
    hs = curl_slist_append(hs, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
}

void altera_disposicao(int tipo, int disposicao, int id = 0)
{

  CURL *curl;
  CURLcode res;
  json j = {};
  std::string readBuffer;
  std::string body;
  std::string path_full = opcoes(tipo, id);
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if (disposicao == 1)
    body = "{ \"disposicao\":" + to_string(true) + "}";
  else
    body = "{ \"disposicao\":" + to_string(false) + "}";
  if (curl)
  {

    // Faz a consulta no banco do tipo de sensor selecionado temperatura ou consumo
    curl_easy_setopt(curl, CURLOPT_URL, path_full.c_str());
    struct curl_slist *hs = NULL;
    hs = curl_slist_append(hs, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
}

int main()
{
  CURL *curl;
  CURLcode res;
  json j;
  string nome;
  string temperatura = "T";
  string consumo = "C";
  string aux = "";
  int opcao, id, disposicao;

  cout << "Digite uma das opcoes: " << endl;
  cout << "1- Lista Sensores de temperatura: " << endl;
  cout << "2- Listar um sensor de temperatura especifico: " << endl;
  cout << "3- Lista Sensores de Consumo " << endl;
  cout << "4- Listar o sensor de consumo com maior consumo: " << endl;
  cout << "5- Alterar o nome de um sensor: " << endl;
  cout << "6- Alterar a disposição de um sensor: " << endl;

  cin >> opcao;

  while (opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 5 || opcao == 6)
  {
    switch (opcao)
    {
    case 1:
      system("clear||cls");
      listar_sensores(1, temperatura);
      break;
    case 2:

      system("clear||cls");
      cout << "Digite o id do sensor de temperatura: " << endl;
      cin >> id;
      listar_sensores(2, temperatura, id);
      break;
    case 3:

      system("clear||cls");
      listar_sensores(1, consumo);
      break;

    case 4:

      system("clear||cls");
      listar_sensores_maior_cosumo(3, "C", 1);
      break;

    case 5:
      system("clear||cls");
      cout << "Digite o id do sensor: " << endl;
      cin >> id;
      cout << "Digite o nome do sensor: " << endl;
      cin >> nome;
      altera_nome(3, nome, id);
      break;

    case 6:
      system("clear||cls");
      cout << "Digite o id do sensor: " << endl;
      cin >> id;
      cout << "Digite a disposicao do sensor: 1 - true ou 2 - false" << endl;
      cin >> disposicao;
      if (disposicao == 1 || disposicao == 2)
        altera_disposicao(4, disposicao, id);
      else
        cout << "Opcao invalida" << endl;

      break;

    default:
      cout << "Opção inválida" << endl;
    }

    cout << "Digite uma das opcoes: " << endl;
    cout << "1- Lista Sensores de temperatura: " << endl;
    cout << "2- Listar um sensor de temperatura especifico: " << endl;
    cout << "3- Lista Sensores de Consumo " << endl;
    cout << "4- Listar o sensor de consumo com maior consumo: " << endl;
    cout << "5- Alterar o nome de um sensor: " << endl;
    cout << "6- Alterar a disposição de um sensor: " << endl;

    cin >> opcao;
  }

  return 0;
}