# Schema attività progetto informatica 

DEFINIZIONI

Definizione file contente piatti

Le informazioni sono contenute all’interno di file di testo CSV con la seguente struttura

Portata

Nome piatto

Ingredienti --> messi dentro a un vettore di 6 elementi, numero massimo di ingredienti

Allergeni --> in totale 7 per le possibili allergie contenute nei piatti

Piatto adatto ai vegani

Piatto adatto ai vegetariani

Piatto adatto a religiosi

Definizione strutture dati per piatti

Uno struct diviso come descritto in precedenza per ogni piatto

Un vettore di piatti per ogni portata 

Definizione strutture dati per menu settimanali

Un vettore di piatti di 7 (giorni della settimana)

Ogni giorno composto da altro vettore di piatti da 5 per le portate

5 menù diversi per gestione differenti esigenze alimentari

ASSUNZIONI

 La quantità prestabilita per ogni ingrediente è sempre 1. Questo è stato fatto per

Non dover gestire anche le quantità degli ingredienti nel file

Non dover gestire le quantità nella gestione del magazzino

Per gestire le quantità serve modificare il codice mettendo dentro lo struct ingredienti un vettore di 6 interi per le quantità, aggiungere le quantità nel controllo del magazzino e del carrello, aggiungere allo struct magazzinoSt un intero per le quantità e aggiungere le quantità all’interno dei file di testo.

Vengono sempre generati 5 menu:

Normale 

Vegano 

Vegetariano 

Religioso 

Allergeni --> per questo vengono chiesti gli allergeni da evitare

FUNZIONALITA’

Implementata funzione per generare i menù in maniera casuale (e non con l’input dall’utente). Questa funzionalità è stata sviluppata soprattutto per poter eseguire agevolmente i test

I menu generati vengono salvati dentro a un file di testo
