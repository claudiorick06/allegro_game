# **🎮 ALLEGRO GAME**

Um jogo 2D de aventura/puzzle, estilo *tile-based*, desenvolvido em C puro com a biblioteca Allegro 5. O jogador deve navegar por diferentes fases, desviando de inimigos e da lava, enquanto coleta todas as frutas para avançar.

Este projeto foi desenvolvido para a disciplina de Programação II da **Universidade Federal Fluminense (UFF)**. 🎓

## **🛠️ Tecnologias Utilizadas**

* **Linguagem:** C  
* **Biblioteca Gráfica:** Allegro 5 (para gráficos, primitivas, fontes, input e áudio)  
* **Canvas (Superfície de Desenho):** ALLEGRO_DISPLAY (Renderização principal do jogo)  
* **Build System:** Make / Makefile

## **🚀 Como Jogar (Versão Pronta)**

Este repositório inclui executáveis pré-compilados na pasta /bin para facilitar os testes em diferentes sistemas operacionais.

### **🐧 Linux (Testado em Ubuntu/Debian)**

1. Clone o repositório e entre na pasta:  
 ```
   git clone https://github.com/claudiorick06/allegro_game.git
   cd allegro_game
 ```

3. Dê permissão de execução ao binário:  
```
chmod +x bin/game_linux
```

5. Execute o jogo:  
```
   ./bin/game_linux
```

### **🍏 macOS**

1. Clone o repositório e entre na pasta:  
```
   git clone https://github.com/claudiorick06/allegro_game.git  
   cd allegro_game
```
3. Dê permissão de execução ao binário:  
```
   chmod +x bin/game_mac
```
4. Execute o jogo:  
```
   ./bin/game_mac
```
### **🪟 Windows**

1. Clone o repositório:  
```
   git clone https://github.com/claudiorick06/allegro_game.git
```
3. Abra a pasta allegro_game no seu explorador de arquivos.  
4. Entre na pasta bin/.  
5. Dê um clique duplo no arquivo game_windows.exe para jogar.

## **👨‍💻 Como Compilar (Para Desenvolvedores)**

Se você deseja compilar o projeto do zero, precisará ter as bibliotecas de desenvolvimento do Allegro 5 instaladas na sua máquina.

### **🐧 Compilando no Linux (Debian/Ubuntu)**

1. Instale as dependências do Allegro 5:  
```
   sudo apt-get install liballegro5-dev liballegro-image5-dev liballegro-font5-dev liballegro-ttf5-dev liballegro-primitives5-dev liballegro-audio5-dev liballegro-acodec5-dev
```
3. Clone o repositório e entre na pasta:  
```
   git clone https://github.com/claudiorick06/allegro_game.git
```
5. Compile o projeto usando o Makefile:  
```
   make all
```
7. O novo executável será criado em output/game. Execute-o:  
```
   ./output/game
```
### **🪟 Compilando no Windows (com MSYS2/MinGW)**

A forma mais fácil de compilar um projeto baseado em Makefile no Windows é usando o **MSYS2**.

1. **Instale o MSYS2:** Baixe e instale o MSYS2 do site oficial ([msys2.org](https://www.msys2.org/)).  
2. **Abra o Terminal MSYS2:** Após a instalação, abra o terminal "MSYS2 MinGW 64-bit".  
3. **Instale as Ferramentas de Build e o Allegro:** Rode o seguinte comando para instalar o GCC, Make e todas as bibliotecas Allegro 5 (isso pode levar alguns minutos):  
```
   pacman -Syu mingw-w64-x86_64-toolchain mingw-w64-x86_64-allegro
```
   (Confirme as instalações pressionando 'Y' quando solicitado).  
5. **Clone o Repositório (dentro do MSYS2):**  
```   
   git clone https://github.com/claudiorick06/allegro_game.git  
   cd allegro_game
```
6. **Compile o Projeto:**  
```
   make
```
8. **Execute:** O executável output/game.exe será criado. Para executá-lo, você precisará copiar os arquivos .dll do Allegro para a pasta output/. Você pode encontrá-los em C:\\msys64\\mingw64\\bin.  
   * Execute make e depois copie as DLLs necessárias (como allegro-5.dll, allegro_image-5.dll, etc.) para a pasta output/ ao lado do seu game.exe.

## **🕹️ Controles**

* **Setas Direcionais:** Movimenta o personagem  
* **F1:** Pula para a próxima fase (modo de debug/teste)  
* **ESC:** Fecha o jogo

## **📂 Estrutura do Projeto**

.  
├── bin/  
│   ├── game_linux        # Executável pré-compilado para Linux  
│   ├── game_mac          # Executável pré-compilado para macOS  
│   └── game_windows.exe  # Executável pré-compilado para Windows  
├── functions/  
│   ├── colision.c        # Lógica de colisão  
│   ├── cria_mapa.c       # Funções para ler e desenhar o mapa  
│   └── moving.c          # Lógica de movimento e animação  
├── images/  
│   ├── fase1.txt         # Arquivos de layout dos mapas  
│   └── ...  
├── structures/  
│   └── objeto.h          # Definição das structs principais (OBJETO, HITBOX)  
├── .gitignore            # Ignora arquivos de build  
├── main.c                # Loop principal do jogo  
├── Makefile              # Regras de compilação  
└── README.md             # Este arquivo

## **📝 Licença**

Este projeto está licenciado sob a Licença MIT.
