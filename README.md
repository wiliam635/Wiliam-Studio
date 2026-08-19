# Wiliam Studio

Base inicial do estúdio de gravação para aulas e demonstrações de teclado.

## Conteúdo

- `index.html`: protótipo visual navegável do estúdio.
- `NamedKeyboard.h`: teclado horizontal baseado em `juce::MidiKeyboardComponent`.
- `ChordDetector.*`: identificação inicial de acordes, inversões e baixo separado.
- `MainComponent.*`: janela JUCE, seleção de dispositivo MIDI e estado visual único.
- `CMakeLists.txt`: configuração para C++20 e JUCE externo.

## Compilação JUCE

Com JUCE instalado localmente:

```bash
cmake -B build -DJUCE_DIR=/caminho/para/JUCE
cmake --build build --config Release
```

O programa usa `juce::MidiKeyboardState` como fonte única das notas. A entrada MIDI é encaminhada ao estado e o teclado gráfico observa esse mesmo estado, evitando duas representações concorrentes das teclas.

## Próximas etapas

1. Separar a cena de gravação da interface de controle.
2. Adicionar captura de duas webcams com `juce::CameraDevice`.
3. Integrar áudio, composição e exportação MP4 via FFmpeg.
4. Persistir modelos de layout e calibração por câmera.
