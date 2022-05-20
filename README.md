# Consegna:

## Esercizio sulle systemcalls

Scrivere un programma in <b>C</b> che effettua le seguenti attivita':

<ul>
    <li> 
        -[x] Il processo padre crea un nuovo file <b>figli.dat</b> e lo apre in lettura e scrittura;
    </li>
    <li>
        -[x] Crea 3 figli e ne scrive i <b>pid</b> e l'ordine di creazione nel file <b>figli.dat</b>;
    </li>
    <li>
        -[x] Al termine della fase di creazione invia il segnale <b>SIGURS1</b> a tutti i figli e termina;
    </li>
    <li>
        -[] I processi figlio appena ricevuto il segnale <b>SIGURS1</b> effettuano un exec;
    </li>
    <li>
        -[] Nel nuovo codice i processi figlio leggono dal file figli.dat il proprio ordine di creazione;
    </li>
    <li>
        -[] Il secondo ed il terzo figlio inviano un segnale <b>SIGURS2</b> al primo figlio;
    </li>
    <li>
        -[] L'ultimo figlio attende tutti i segnali dei fratelli e termina.
    </li>
</ul>
