# Wiliam Studio

Base inicial do estúdio de gravação para aulas e demonstrações de teclado.

## Conteúdo

- `index.html`: protótipo visual navegável do estúdio.
- `NamedKeyboard.h`: teclado horizontal baseado em `juce::MidiKeyboardComponent`.
- `ChordDetector.*`: identificação inicial de acordes, extensões, inversões e baixo separado.
- `MainComponent.*`: janela JUCE, seleção de dispositivo MIDI e estado visual único.
- `CMakeLists.txt`: configuração para C++20 e JUCE externo.

## Compilação JUCE

Com JUCE instalado localmente:

```bash
cmake -B build -DJUCE_DIR=/caminho/para/JUCE
cmake --build build --config Release
```

O programa usa `juce::MidiKeyboardState` como fonte única das notas. A entrada MIDI é encaminhada ao estado e o teclado gráfico observa esse mesmo estado, evitando duas representações concorrentes das teclas. O detector reconhece tríades, sus, diminutos, aumentados, acordes com 6, 7, maj7, 9, maj9, add9 e inversões com baixo separado.

## Próximas etapas

1. Separar a cena de gravação da interface de controle.
2. Adicionar captura de duas webcams com `juce::CameraDevice`.
3. Integrar áudio, composição e exportação MP4 via FFmpeg.
4. Persistir modelos de layout e calibração por câmera.
