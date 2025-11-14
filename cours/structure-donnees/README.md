# Structure de données

## Comparaison Vecteur/Listes chainées

| Opération              | Vecteur | Liste Chainée | Liste doublement chainée |
| ---------------------- | ------- | ------------- | ------------------------ |
| Accès début            | const   | const         | const                    |
| Accès fin              | const   | lin           | const                    |
| Accès arbitraire       | lin     | lin           | const                    |
| Insertion fin          | lin     | lin           | const                    |
| Insertion début        | lin     | const         | const                    |
| Insertion arbitraire   | lin     | lin           | lin                      |
| Suppression début      | lin     | const         | const                    |
| Suppression arbitraire | lin     | lin           | lin                      |


## TP 1 - Performances Vecteurs/Listes Chainées/Listes Doublement Chainées

```sh
========== Vecteur de base ==========

Tableau chargé en 3.228 ms
Memoire utilisée pour 4058504 elements: 4.059Mo
26 parcours de tableau et 3356198 appels à la fonction rechercher en 54.324 ms

========== Vecteur avec 50 charactères de plus ==========

Tableau chargé en 1.761 ms
Memoire utilisée pour 4058554 elements: 4.059Mo
26 parcours de tableau et 3356198 appels à la fonction rechercher en 54.522 ms

========== Liste chainée ==========

Tableau chargé en 132.875 ms
Memoire utilisée pour 4058504 elements: 64.936Mo
26 parcours de tableau et 3356198 appels à la fonction rechercher en 235.355 ms

========== Liste doublement chainée ==========

Tableau chargé en 96.384 ms
Memoire utilisée pour 4058504 elements: 97.404Mo
26 parcours de tableau et 3356198 appels à la fonction rechercher en 231.770 ms
```
