# OpenGL Exercises

Este repositório contém exercícios relacionados ao uso do OpenGL.

## Como compilar o projeto

Use o seguinte comando para compilar o projeto:

```bash
g++ -g -std=c++17 -I include -L lib main.cpp src/CreateBasicTriangle.cpp src/ApplyTransformationTriangle.cpp src/CreateBasicSquare.cpp src/ShaderSources.cpp src/glad.c -lglfw3dll -o opengl_app.exe
```

Certifique-se de que as bibliotecas e os arquivos necessários estejam corretamente configurados.

## Como executar o projeto

Após compilar, você pode executar o programa com os seguintes argumentos:

- `S`: Gera um quadrado.
- `T`: Gera um triângulo.

Exemplo de execução:

```bash
./opengl_app.exe S
```

ou

```bash
./opengl_app.exe T
```

## Referência

Para configurar o ambiente e aprender mais sobre OpenGL, consulte o seguinte tutorial:  
[Tutorial de OpenGL para Iniciantes](https://terminalroot.com.br/2024/02/tutorial-de-opengl-para-iniciantes.html)
