# SAE1.02

# Guide pour lancer l'application

## Prérequis
Assurez-vous d'avoir les éléments suivants installés sur votre système :
- [Git](https://git-scm.com/)
- [Make](https://www.gnu.org/software/make/)
- [GCC](https://gcc.gnu.org/)

## Étapes

1. **Cloner le dépôt Git :**
   ```bash
   $ git clone https://codefirst.iut.uca.fr/git/matheo.hersan/SAE1.02.git
   $ cd SAE1.02
2. **Exécuter le script de lancement :**
   ```bash
   $ ./build.sh -rbuild
Cette commande nettoie, construit et exécute l'application.

3. **Optionnel - Nettoyer les fichiers générés :**
   Pour nettoyer les fichiers générés (objets, exécutable et documentation doxygen), utilisez l'option `-clean` :
   ```bash
   $ ./build.sh -clean
4. **Exécuter l'application (après la construction) :**
   Si vous avez déjà construit l'application et souhaitez simplement l'exécuter, utilisez l'option `-run` :
   ```bash
   $ ./build.sh -run
**Notes**
- Assurez-vous que le script (`build.sh`) a les permissions d'exécution :
   ```bash
   $ chmod +x build.sh
- Si vous ne spécifiez aucune option lors de l'exécution du script, il affichera un message d'erreur vous indiquant d'utiliser --help pour afficher l'aide :
   ```bash
   $ ./build.sh --help
- En cass d'erreurs imprévus avec le script `build.sh` faite simplement un :
   ```bash
   $ make all
   $ ./app
