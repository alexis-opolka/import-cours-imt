#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** --------------------------------------------------------------------------------------------------------
 *                                                Global variables
 *  -------------------------------------------------------------------------------------------------------- */

static char* ResulCodetStrings[] = {
  "Ok", "Compte non trouvé", "Solde insuffisant"
};

/** --------------------------------------------------------------------------------------------------------
 *                                                Custom Types
 *  -------------------------------------------------------------------------------------------------------- */

typedef enum ResultCode {
  ok = 0,
  compte_non_trouve = 1,
  solde_insuffisant = 2
} ResultCode;

typedef union ErreurInfo {
  char* account_name;
  int* account_value;
} ErreurInfo;

typedef struct Result {
  int account_index;
  ResultCode exit_status;
  ErreurInfo error_info;
} Result;

typedef struct User {
  int id;
  int account_value;
  char* name;
} User;


/** --------------------------------------------------------------------------------------------------------
 *                                                FUNCTIONS
 *  -------------------------------------------------------------------------------------------------------- */
void affiche_erreur(Result* erreur) {
  printf("Erreur: %s\n", ResulCodetStrings[erreur->exit_status]);
}

void affiche_erreur_extensive(Result* erreur) {
  if (erreur->exit_status == compte_non_trouve) {

    // Si le compte est non trouvé, on affiche l'erreur, avec le nom recherché
    printf("Erreur: Compte %s non trouvé !\n", erreur->error_info.account_name);
  } else if (erreur->exit_status == solde_insuffisant) {

    // Si le solde est insuffisant, on affiche l'erreur, avec le solde
    printf("Erreur: Solde insuffisant, vous n'avez que %d sur votre compte !\n", *erreur->error_info.account_value);
  }
}

/**
  Cette fonction trouve un compte dans la liste des comptes en utilisant le nom de l'utilisateur
  Elle renvoie la position du compte dans la liste des comptes
*/
Result trouver_compte(User* comptes, char* user_a_trouver, int* nbr_comptes){
  // This is the fallback result, if not found, the members are not changed
  Result result = {.account_index = -1, .exit_status = compte_non_trouve, .error_info.account_name = user_a_trouver};

  for (int i = 0; i < *nbr_comptes; i++){
    if (strcmp((comptes[i].name), user_a_trouver) == 0){
      // We update the result struct to send back the correct values
      result.account_index = i;
      result.exit_status = ok;
    }
  }


  return result;
}

/**
  Cette fonction permet de déposer de l'argent sur un compte
  Elle renvoie l'identifiant du compte sur lequel l'argent à été trouvé et -1 si il n'a pas été trouvé ou si le solde était insuffisant
*/
Result retrait_argent(User* comptes, char* user, int* nbr_comptes){
  Result result = {.account_index = -1, .exit_status = solde_insuffisant};

  printf("quel est le montant du retrait ?");

  int montant;
  scanf("%d", &montant);

  Result compte = trouver_compte(comptes, user, nbr_comptes);
  if (compte.exit_status == compte_non_trouve){
    // We forward the return result from trouver_compte
    // to this function's result
    result = compte;
  } else {
    // We handled the case where the account number was undefined
    // then we can assign it to the result struct
    result.account_index = compte.account_index;

    if (comptes[compte.account_index].account_value > montant){
      // We update the result struct with the correct exit status
      comptes[compte.account_index].account_value -= montant;
      result.exit_status = ok;
    } else {
      // Here just in case we have an issue that wasn't handled properly
      result.error_info.account_value = &comptes[compte.account_index].account_value;
    }
  }

  return result;
}

void create_account(User* comptes, User new_user, int* nbr_comptes) {
  int* new_count = malloc(sizeof(int));
  new_count = nbr_comptes+1;

  printf("DEBUG Taille: %d\n", *new_count);

  User* newtab = malloc(sizeof(User) * (*new_count));
  for (int i = 0; i < *new_count; i++) {
    newtab[i] = comptes[i];

    printf("DEBUG: %s\n", newtab[i].name);
    printf("DEBUG: %d\n", newtab[i].account_value);
  }

  
  newtab[*new_count] = new_user;
  free(comptes);
  
  nbr_comptes = new_count;
  comptes = newtab;
}

int quit(){
  printf("Centaurustasie's Bank at your service, Goodbye!\n");
  exit(0);
}

/** --------------------------------------------------------------------------------------------------------
 *                                                MAIN
 *  -------------------------------------------------------------------------------------------------------- */

int main(){
  User comptes[] = {
    {.id = 5, .account_value = 500, .name = "mlk"},
    {.id = 12, .account_value = 60, .name = "fdm"},
    {.id = 7, .account_value = 12700, .name = "sdb"}
  };

  // On fait un rapide compte du nombre de comptes enregistrés
  int nbr_comptes = sizeof(comptes)/sizeof(User);

  // Getting a name
  char nom_compte[4];
  printf(
    "Centaurustasie's Bank at your service, Hi!\n"
    "Veuillez entrer votre nom\n"
  );
  scanf(" %c%c%c", nom_compte, nom_compte + 1, nom_compte + 2);
  nom_compte[3] = 0;

  printf("Welcome back %c%c%c!\n", nom_compte[0], nom_compte[1], nom_compte[3]);

  while (1){
    char operation;


    // Getting the operation requested
    printf("quelle opération souhaitez vous effectuer ?"
      "\n\tTapez a pour afficher votre solde"
      "\n\tTapez r pour effectuer un retrait"
      "\n\tTapez n pour ajouter un compte"
      "\n\tTapez q pour quitter ce shell\n");
    scanf(" %c", &operation);

    switch (operation)
    {
      // Case to create a new account
      case 'n':
        User new_account = {.name = nom_compte, .id = comptes[nbr_comptes].id+1};

        printf("You don't have an account? Let's solve that!\n");
        printf("Quel solde souhaitez-vous déposer:");
        scanf(" %d", &new_account.account_value);

        create_account(comptes, new_account, &nbr_comptes);

      // Case to show the current value our account has
      case 'a':
        Result compte = trouver_compte(comptes, nom_compte, &nbr_comptes);

        if (compte.exit_status == compte_non_trouve){
          affiche_erreur_extensive(&compte);

          printf("Erreur: votre compte n'a pas été trouvé\n");
        } else {
          printf("Le solde de votre compte est : %d\n", comptes[compte.account_index].account_value);
        }

      // Case to retrieve money
      case 'r':
        Result result = retrait_argent(comptes, nom_compte, &nbr_comptes);

        if (result.exit_status == solde_insuffisant){
          affiche_erreur_extensive(&result);

          printf("erreur lors du retrait, l'opération n'a pas été effectuée\n");
        } else {
          printf("la somme a bien été retirée du compte n° %d\n", result.account_index);
        }

      // Case to quit the bank shell
      case 'q':
        quit();

      default:
        printf("Unrecognized operation! Please try again.\n");
    }
  }
}

