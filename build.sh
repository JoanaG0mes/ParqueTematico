#!/bin/bash

# Este script compila e instala TODOS os seus programas CGI no XAMPP
# com a correção "-static-libstdc++" para o erro 'GLIBCXX'.
#
# Execute-o a partir da sua pasta /home/joana/ParqueTematico
# com o comando: sudo ./build.sh

# Limpa a tela para uma visualização limpa
clear
echo "============================================="
echo " 🚀 Iniciando o Build do Projeto Parque Temático 🚀"
echo "============================================="
echo "A compilar com 'static-libstdc++' para corrigir o Erro 500..."
echo ""

# --- 1. Compilar o Teste de Diagnóstico ---
echo "--- 1. Compilando teste.cgi (Diagnóstico) ---"
g++ /home/joana/ParqueTematico/cgi/teste.cpp -o /opt/lampp/cgi-bin/teste.cgi -static-libstdc++

# Verifica se a compilação falhou
if [ $? -ne 0 ]; then
    echo "❌ ERRO FATAL ao compilar teste.cgi!"
    echo "O build foi interrompido."
    exit 1 # Para o script
fi
echo "✅ teste.cgi compilado com sucesso."
echo ""

# --- 2. Compilar o Cadastro (Projeto) ---
echo "--- 2. Compilando cadastro.cgi (Projeto) ---"
g++ /home/joana/ParqueTematico/cgi/cadastro.cpp -I /home/joana/ParqueTematico/include -o /opt/lampp/cgi-bin/cadastro.cgi -static-libstdc++

if [ $? -ne 0 ]; then
    echo "❌ ERRO FATAL ao compilar cadastro.cgi!"
    echo "Verifique os seus #includes ou erros de sintaxe."
    echo "O build foi interrompido."
    exit 1
fi
echo "✅ cadastro.cgi compilado com sucesso."
echo ""

# --- 3. Compilar o Painel (Projeto) ---
echo "--- 3. Compilando painel.cgi (Projeto) ---"
g++ /home/joana/ParqueTematico/cgi/painel.cpp -I /home/joana/ParqueTematico/include -o /opt/lampp/cgi-bin/painel.cgi -static-libstdc++

if [ $? -ne 0 ]; then
    echo "❌ ERRO FATAL ao compilar painel.cgi!"
    echo "Verifique os seus #includes ou erros de sintaxe."
    echo "O build foi interrompido."
    exit 1
fi
echo "✅ painel.cgi compilado com sucesso."
echo ""

# --- 4. Compilar a Remoção (Projeto) ---
echo "--- 4. Compilando remover.cgi (Projeto) ---"
g++ /home/joana/ParqueTematico/cgi/remover.cpp -I /home/joana/ParqueTematico/include -o /opt/lampp/cgi-bin/remover.cgi -static-libstdc++

if [ $? -ne 0 ]; then
    echo "❌ ERRO FATAL ao compilar remover.cgi!"
    echo "Verifique os seus #includes ou erros de sintaxe."
    echo "O build foi interrompido."
    exit 1
fi
echo "✅ remover.cgi compilado com sucesso."
echo ""


# --- 5. Aplicar Permissões ---
echo "--- 5. Aplicando Permissões... ---"
chmod +x /opt/lampp/cgi-bin/teste.cgi
chmod +x /opt/lampp/cgi-bin/cadastro.cgi
chmod +x /opt/lampp/cgi-bin/painel.cgi
chmod +x /opt/lampp/cgi-bin/remover.cgi

# Permissões para a base de dados (só por garantia)
# Certifique-se que o diretório /opt/lampp/database exista!
chmod
