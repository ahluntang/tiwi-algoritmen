
* gedrag van echte mieren
    * mieren zoeken kortste paden tussen voedelbronnen en hun nest
    * mieren zetten *pheromones* (geursporen) af op op hun weg
    * bij het kiezen in welke richting ze gaan, grotere kans dat een pad gekozen wordt dat gemarkeerd werd door een sterker *pheromone*
    * na verloop van tijd vinden mieren juiste pad
    = coöperatieve interactie, leidt tot kortste paden

## Methode

```
InitializePheromoneValues(T) // alle geursporen op beginwaarden zetten
while termination conditions not met do
    for all ants a from A do
        s_a ← ConstructSolution(T,H) // elke mier bouwt incrementeel oplossing en voegt componenten toe
    endfor
    ApplyOnlineDelayedPheromoneUpdate(T, {s_a| a from A}) // pheromonen aanpassen
```

* component per component geconstrueerd
* elke mier \\(a\\) uit de set van mieren \\(\mathcal{A}\\) probeert complete oplossing \\(s_a\\) te construeren in elke iteratie
    * door component per component aan toe te voegen
* via constructiegraaf (dichte graaf)
    * knopen zijn componenten
    * van elke component \\(c_l\\) kan je naar elke andere component \\(c_r\\)
        * naar andere component: via random manier
    * verbindingen \\(l_{i,j} \in \mathcal{L}\\) krijgen "geurspoor" \\(\mathcal{T}_i\\)
        * weg met grotere geurspoor: grotere kans (*transition probability*) dat een mier deze weg neemt/volgt
            * kans dat je naar \\(c_r\\) gaat als je in \\(c_l\\) zit:
              \\[
                    P(c_r|s_a[c_l]) = 
                    \begin{cases}
                        0  & \text{als $c_r$ tot oplossing leidt die niet doenbaar/feasible is} (c_r \notin J(s_a[c_l])) \\\
                        \frac{[\eta_r]^{\alpha}[\tau_r]^{\beta}}{ \sum_{c_u \in J(s_a[c_l])}{[\eta_u]^{\alpha} [\tau_u]^{\beta}} } & \text{als } (c_r \in J(s_a[c_l]))  \\\
                    \end{cases}
              \\]
              noemer: normalisatie, som van alle componenten die feasible zijn (om <= 1 te verkrijgen)
              teller: eigenlijke voorwaarde
              \\(\alpha \\) en \\(\beta\\) : machten die gekozen worden
        * geuren verdwijnen na periode
            * om invloed ervan geleidelijk te laten verdwijnen (als het bv. geen goede opl. zou zijn)
    * mieren gaan niet naar componenten die niet *feasible* is
    * mier kan gestuurd worden door 4 verschillende parameters
* deze oplossingen kunnen dan gebruikt worden om de pheromonen bij te werken
* updates
    * **online**
        * **delayed**
            * wachten tot alle mieren klaar zijn
            * oplossing overlopen en geuren toevoegen
            \\[ \tau_j \leftarrow (1-\rho)\tau_j + \sum_{a \in \mathcal{A}}{\varDelta\tau_j^{s_a}} \\]
            \\((1-\rho)\tau_j\\) : om lokale putten vermijden, verzwakt vorige geur
            \\(\sum_{a \in \mathcal{A}}{\varDelta\tau_j^{s_a}}\\) : nieuwe geuren van mier \\(a\\) komen erbij, grootte hangt af van hoe goed oplossing wel is
        * **step-by-step**
            * uitbreiding: voor Ant Colony System
            * tijdens constructie geuren ook toevoegen (niet wachten tot mieren klaar zijn)
    * **offline**
        * *supervisor* vergelijkt oplossingen
        * interessante oplossingen sterker maken
        * mier op zich kan dit niet: kent andere mieren niet

## Ant Colony System

```
while termination conditions not met do
    ScheduleActivities
        AntBasedSolutionconstruction()
        PheromoneUpdate()
        DaemonActions()
    end ScheduleActivities
endwhile
```

* gevorderder systeem: wat er gebeurt tijdens iteratie vager omschreven
    * ScheduleActivities
        * constructie
        * geuren updaten
        * daemon actions
            * om gecentraliseerde acties uit te voeren die niet door mieren zelf individueel kunnen uitgevoerd worden
            * werkt geuren offline bij op het einde van iteratie
* origineel: enkel geurwaarden bij componenten
    * gevorderd: ook bij verbindingen
* meer variatie
* *pseudo-random-proportional rule*
    * determinitisch oplossing zoeken: niet enkel op kans, maar bv op bepaalde waarden
* *MMAS*: Max-Min Ant System
    * geur kan nooit minder zijn dan bepaalde waarde
    * ervoor zorgen dat er steeds kans blijft dat mier naar elk component kan gaan

