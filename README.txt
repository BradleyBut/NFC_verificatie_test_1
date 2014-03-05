Op de server staat een aantal ID's deze server is locaal dus kan je zelf niet berijken.
het probleem op dit moment is niet de data van de server afhalen maar het filteren.

dit krijg ik binnen als ik programma NFC_verificatie_2 uitvoer

HTTP/1.1 200 OK
Content-Length: 170
Content-Type: text/html
Last-Modified: Fri, 07 Feb 2014 09:17:26 GMT
Accept-Ranges: bytes
ETag: "5951e36ae523cf1:c47"
Server: Microsoft-IIS/6.0
X-Powered-By: ASP.NET
Date: Wed, 05 Mar 2014 07:30:56 GMT
Connection: close

DASMLcardid:
0x4 0x22 0x47 0x5A 0x77 0x32 0x80 Read card #1517761152 ID card =#1517761200
0x4 0x59 0x3F 0x12 0x94 0x2A 0x80 Read card #311700096 ID card =#311700100
we willen alleen maar wat onder DASMLcardid: staat hebben voor op de sd kaart.
als dit van de server naar de sd kaart geschreven is wat ongeveer om de uur gerefresht moet worden.
dan is het de bedoeling dat wanneer iemand zijn pas langs de scanner houdt dus wanneer het ID iets anders is dan 0
dat er dan gezocht wordt of het ID overeenkomt met het een van de ID's die op de SD kaart staan. als dit zo is wordt er
een relai omgeschakeld die op een digitale output zit aangesloten deze blijft dan HIGH todat er een input hoog wordt.
dit steld een knop voor die men kan indrukken wanneer ze klaar zijn met het gebruik van de machine waar de toegang voor
nodig was.

er wordt gebruik gemaakt van de NFC shield V2.0b by Seeed Studio, een orginele Ethernet shield. en een arduino mega ADK

Gevonden problemen:

De shields werken niet goed samen ivbm de SPI.
om dit te omzeilen heb ik het volgende gevonden
gebruik SPI.setDataMode(MODE1) voor de NFC en SD
gebruik SPI.setDataMode(MODE0) voor de ethernet

standaart staat hij op MODE0 daarom staat dit op dit moment niet aangegeven in het programma.

NFC_verificatie_test_1
hier staat een voorbeeld programma in hoe er gefilterd wordt. alleen wij filteren dan niet wat er tussen < en > staat maar,
is het de bedoeling dat hij pas begint te lezen bij DASMLcardid:
  
