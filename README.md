# Gestionale mensa — generazione dei menu e gestione delle scorte

**Tipologia:** progetto scolastico finale **di gruppo**  
**Tecnologie:** C++, file di testo, HTML, CSS, JavaScript  
**Contributo personale documentato:** supporto allo sviluppo software del componente gestionale (nel manuale originale: «aiuto software developer»).

## Obiettivo

Sperimentare la progettazione di un gestionale per una mensa/ristorante immaginario chiamato **ScamPizza**, in grado di comporre un menu settimanale e gestire alternative alimentari e disponibilità di ingredienti.

Il lavoro comprende un programma C++ da console, dati testuali per piatti e scorte, una raccolta di pagine web dimostrative e documentazione di progetto.

## Funzionalità implementate/progettate nel codice

- Scelta tra generazione **casuale** del menu e selezione **manuale** delle portate.
- Organizzazione su **sette giorni**, ciascuno con cinque portate: antipasto, primo, secondo, contorno, dolce.
- Preparazione di menu alternativi per esigenze alimentari (vegani, vegetariani, restrizioni religiose, allergeni indicati dall'utente).
- Lettura dei piatti e delle disponibilità di magazzino da file di testo.
- Gestione di un carrello di ingredienti mancanti e verifica rispetto a un budget iniziale.
- Esportazione dei menu generati su `menuSettimana.txt`.
- Pagine HTML/CSS per presentazione del ristorante e dei menu, con interazioni JavaScript.

> Queste sono funzionalità previste dai sorgenti e dalla documentazione. La versione consegnata presenta difetti che possono impedirne l'uso completo: non è descritta come software di produzione.

## Struttura rilevante dell'archivio originale

```text
progetto finale informatica/
├── gestionale mensa/
│   └── gestionale mensa/
│       └── main.cpp
├── antipasti.txt
├── primi.txt
├── secondi.txt
├── contorni.txt
├── dolci.txt
├── magazzino.txt
├── menuSettimana.txt
├── forseFunziona/         # pagine web e risorse statiche
├── UmlFinale.dia
├── manuale-uso-it.md
├── user-manual-en.md
├── schema-attivita.md
└── schema-test.md
```

## Requisiti e avvio

Per la parte gestionale è necessario un compilatore C++ con supporto almeno a C++17. Per la parte web è sufficiente un browser, mentre alcune pagine possono richiedere risorse esterne.

### Compilazione del componente C++

Il comando **indicativo**, dalla cartella contenente `main.cpp`, è:

```bash
g++ -std=c++17 main.cpp -o gestionale_mensa
```

**Attenzione:** la versione originale non risulta compilabile senza interventi con una toolchain standard. Per esempio, usa `strtok` senza includere esplicitamente il relativo header; sono presenti anche dichiarazioni e accessi che meritano correzioni. Questo comando è quindi una traccia per la versione corretta, **non** una garanzia che quella caricata compili.

### Percorsi da correggere

`main.cpp` utilizza percorsi assoluti di tipo `/Users/.../testfile/...` per leggere i file dei piatti e del magazzino, generare il file dei menu e aprire pagine web. Prima di tentare l'avvio occorre sostituirli con percorsi relativi corretti e verificare la presenza dei file richiesti.

Dopo la correzione dei problemi, il funzionamento previsto è: scegliere generazione manuale/casuale, indicare gli allergeni da evitare, comporre i menu, consultare il carrello e il file generato.

### Visualizzazione della parte web

La pagina principale si trova in `forseFunziona/ristornate.html`. È possibile aprirla in un browser dalla cartella originale. I file HTML, CSS e JS sono statici e **non è dimostrata un'integrazione dinamica automatica** con il programma C++.

## Limiti tecnici noti

- Possibili accessi a indici fuori intervallo (in particolare `i - 1` quando `i = 0`, oppure accesso dopo ricerca terminata con `-1`).
- Problemi di compilazione e portabilità su sistemi diversi da quello di sviluppo.
- Percorsi assoluti incorporati nel codice.
- Strutture dati di dimensione fissa, con controlli sulle capienze da completare.
- Modello delle scorte semplificato: nel progetto ogni ingrediente viene contato come una porzione unitaria, non come una quantità fisica in grammi.
- Le pagine web comprendono immagini e librerie di terzi: verificare origine e licenza prima di una pubblicazione pubblica.

## Collaborazione e attribuzione

Il materiale originale identifica **più partecipanti** con ruoli diversi (sviluppo software, supporto allo sviluppo, web e progettazione). Questo repository va quindi presentato come **lavoro di gruppo**, distinguendo il contributo individuale dalla realizzazione complessiva. Per il dettaglio dei contributi si rimanda al manuale d'uso presente nel repository.

## Competenze illustrate

Lettura/scrittura su file, strutture e array C++, controllo degli input, gestione di vincoli, progettazione UML, documentazione e collaborazione a un progetto software.

## Materiale pubblicato

La relazione personale sul lavoro di gruppo è esclusa dalla pubblicazione. Le 119 immagini fotografiche e grafiche del sito (JPG, JPEG e PNG) sono escluse dalla pubblicazione. Le pagine HTML conservano i riferimenti originali: le relative immagini non saranno visualizzate.

I manuali sono forniti in versione testuale Markdown. I documenti Word originali e la presentazione PDF illustrata sono esclusi; la documentazione testuale è disponibile in Markdown.
