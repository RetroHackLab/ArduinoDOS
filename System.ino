#include <EEPROM.h>

// =========================================================================
// 🌐 GLOBAL CONFIGURATION & OS STATES (RetroHackLab)
// =========================================================================
enum OperatingMode { MODE_CONSOLE, MODE_USER, MODE_SETUP };
OperatingMode currentMode = MODE_CONSOLE;
bool isSuperUser = false;
bool isWritingFile = false;

String currentFilename = "";
String systemCountry = "Tunisia";
String systemLanguage = "EN";         // 🇬🇧 Default Language = English
String textTextColor = "\033[0;32m";  // Default ANSI Green
const String adminPassword = "retrohack";

void setup() {
    Serial.begin(115200);
    while (!Serial) { ; }

    // =========================================================================
    // 🚀 RETRO BOOT SEQUENCE (Icon, Loading & Title)
    // =========================================================================
    Serial.print(textTextColor);
    
    // 1. Arduino Icon & "Startup Arduino" text
    Serial.println(F("       _     _ "));
    Serial.println(F("     /   \\ /   \\"));
    Serial.println(F("    |  +  |  -  |"));
    Serial.println(F("     \\ _ / \\ _ /"));
    Serial.println(F("  --- ARDUINO UNO ---"));
    Serial.println(F("[*] Startup Arduino..."));
    delay(600);
    Serial.println();

    // 2. DOS Step - Loading system files
    Serial.println(F("Fetching System Files ....."));
    delay(500);
    Serial.println(F("Prepare Modes........"));
    delay(500);
    Serial.println(F("Setting Up........"));
    delay(500);
    Serial.println(F("Finishing...."));
    delay(400);
    Serial.println();

    // 3. Official OS Title before access
    Serial.println(F("=================================================="));
    Serial.println(F("                  ArduinoDOS                      "));
    Serial.println(F("=================================================="));
    Serial.print(F("\033[0m")); // Temporary color reset
    
    // Direct link to the standard console mode
    printPrompt();
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        input.trim(); // Nettoie les retours à la ligne (\r et \n)
        
        if (input.length() > 0) {
            if (isWritingFile) {
                if (input == F("#end#")) {
                    isWritingFile = false;
                    Serial.print(textTextColor);
                    Serial.print(F("[Editor] Fichier '"));
                    Serial.print(currentFilename);
                    Serial.println(F("' sauvegarde et complet.\033[0m"));
                } else {
                    Serial.print(F("  [>>] "));
                    Serial.println(input); 
                }
            } else {
                executeCommand(input);
            }
        }
        if (!isWritingFile) printPrompt();
    }
}

// =========================================================================
// 🖥️ DYNAMIC PROMPT RENDERING
// =========================================================================
void printPrompt() {
    Serial.print(textTextColor); 
    if (currentMode == MODE_CONSOLE) {
        if (isSuperUser) Serial.print(F("root@uno# \033[0m"));
        else Serial.print(F("arduino@uno$ \033[0m"));
    } 
    else if (currentMode == MODE_USER) {
        Serial.print(F("base_use$ \033[0m"));
    } 
    else if (currentMode == MODE_SETUP) {
        Serial.print(F("arduino@uno(SETUP)# \033[0m"));
    }
}

// =========================================================================
// ⚙️ CENTRAL COMMAND ENGINE
// =========================================================================
void executeCommand(String cmd) {
    
    // -------------------------------------------------------------------------
    // ⚙️ CONFIGURATION MODE (SETUP)
    // -------------------------------------------------------------------------
    if (currentMode == MODE_SETUP) {
        
        if (cmd.startsWith(F("LG -"))) {
            systemLanguage = cmd.substring(4);
            systemLanguage.toUpperCase();
            Serial.print(F("[Language] System language changed to: "));
            Serial.println(systemLanguage);
        }
        else if (cmd == F("UPTIME")) {
            unsigned long secs = millis() / 1000;
            Serial.print(F("[Time] System Uptime: ")); Serial.print(secs); Serial.println(F("s | Date: 25/05/2026"));
        }
        else if (cmd.startsWith(F("COUNTRY"))) {
            if (cmd.length() > 8) {
                systemCountry = cmd.substring(8);
                Serial.print(F("[Region] Country changed to: "));
                Serial.println(systemCountry);
            } else {
                Serial.print(F("[Region] Current Region: "));
                Serial.println(systemCountry);
            }
        }
        else if (cmd == F("DEVICE.mvbx")) {
            Serial.println(F("--- DEVICE INFO ---"));
            Serial.println(F("Hardware: Arduino Uno (ATmega328P)"));
            Serial.println(F("Architecture: 32-bit (Emulated Engine)"));
            Serial.println(F("OS Engine: ArduinoDOS v1.5"));
            Serial.println(F("Developer: RetroHackLab"));
        }
        else if (cmd == F("UPDATE.mvbx")) {
            Serial.println(F("[Update] Checking channels... Status: Up to date."));
        }
        else if (cmd == F("VERIFY M")) {
            Serial.println(F("[Analyse] Analyse globale de la structure des fichiers SETUP... OK (0 Errors)"));
        }
        else if (cmd == F("vm GREEN")) {
            textTextColor = "\033[0;32m";
            Serial.println(F("\033[0;32m[UI] Mode Couleur Vert Active."));
        }
        else if (cmd == F("vm WHITE")) {
            textTextColor = "\033[0;37m";
            Serial.println(F("\033[0;37m[UI] Mode Couleur Blanc Active."));
        }
        else if (cmd.startsWith(F("EXIT & C \""))) {
            int endQuote = cmd.indexOf('"', 10);
            if (endQuote != -1) {
                String targetMode = cmd.substring(10, endQuote);
                if (targetMode == F("arduino@uno")) {
                    currentMode = MODE_CONSOLE;
                    Serial.println(F("[SETUP] Modification terminee. Retour a la console native."));
                } else if (targetMode == F("base_use")) {
                    currentMode = MODE_USER;
                    isSuperUser = false;
                    Serial.println(F("[SETUP] Modification terminee. Redirection vers le Mode User Simple."));
                } else {
                    Serial.println(F("\033[0;31m[ERROR] Mode inconnu. Utilisez \"arduino@uno\" ou \"base_use\"\033[0m"));
                }
            }
        }
        else {
            Serial.println(F("\033[0;31mCommand Not found or Unsupported Mode\033[0m"));
        }
        return;
    }

    // -------------------------------------------------------------------------
    // 🛠️ SHARED COMMANDS (CONSOLE & USER MODE)
    // -------------------------------------------------------------------------
    if (cmd.startsWith(F("VERIFY "))) {
        String path = cmd.substring(7);
        Serial.print(F("[Verification] Analyse et preview de l'integrite du fichier a: "));
        Serial.println(path);
        return;
    }

    if (cmd.startsWith(F("touch "))) {
        String target = cmd.substring(6);
        if (target.endsWith(F("/"))) {
            Serial.println(F("Folder Creation Done"));
        } else {
            currentFilename = target;
            isWritingFile = true;
            Serial.print(F("[Editor] Ecriture dans '"));
            Serial.print(currentFilename);
            Serial.println(F("' active. Tapez '#end#' pour sauvegarder."));
        }
        return;
    }

    if (cmd.startsWith(F("set "))) {
        int firstSpace = cmd.indexOf(' ', 4);
        if (firstSpace == -1) { Serial.println(F("\033[0;31m[ERROR] Syntaxe: set *file* *permission*\033[0m")); return; }
        
        String file = cmd.substring(4, firstSpace);
        String perm = cmd.substring(firstSpace + 1);

        if (file.endsWith(F("/"))) {
            if (perm == F("main/tree")) {
                Serial.print(F("[Perm] Dossier '")); Serial.print(file); Serial.println(F("' -> main/tree [Arborescence OK]"));
            } else {
                Serial.println(F("\033[0;31m[ERROR] Utilisez main/tree pour les dossiers.\033[0m"));
            }
            return;
        }

        if (perm == F("root/mine")) { Serial.print(F("[Perm] '")); Serial.print(file); Serial.println(F("' -> root/mine [Execution Console OK]")); }
        else if (perm == F("root/debug")) { Serial.print(F("[Perm] '")); Serial.print(file); Serial.println(F("' -> root/debug [Debugging Actif]")); }
        else if (perm == F("root/content")) { Serial.print(F("[Perm] WARNING: root/content applique (Utility seulement - Non recommande)")); }
        else if (perm == F("su/R")) { Serial.print(F("[Perm] '")); Serial.print(file); Serial.println(F("' -> su/R [Modification Subregistry Autorisee]")); }
        else if (perm == F("root/git")) { Serial.print(F("[Perm] '")); Serial.print(file); Serial.println(F("' -> root/git [Code Source Identifie]")); }
        else if (perm == F("lock/encrypt")) { Serial.print(F("[Perm] '")); Serial.print(file); Serial.println(F("' -> lock/encrypt [Script Re-chiffrement Console Obligatoire]")); }
        else if (perm == F("lock/decrypt")) { Serial.print(F("[Perm] '")); Serial.print(file); Serial.println(F("' -> lock/decrypt [Script Dechiffrement Console Obligatoire]")); }
        else { Serial.println(F("\033[0;31m[ERROR] Permission inconnue.\033[0m")); }
        return;
    }

    if (cmd == F("su -C")) {
        if (currentMode == MODE_USER) { Serial.println(F("\033[0;31mCommand Not found or Unsupported Mode\033[0m")); return; }
        
        Serial.print(F("\033[0;33m[AUTH] Entrez le mot de passe Administrateur : \033[0m"));
        while (!Serial.available());
        String pass = Serial.readStringUntil('\n'); 
        pass.trim(); // <-- Crucial : Supprime le \r invisible pour valider le mot de passe
        
        if (pass == adminPassword) {
            isSuperUser = true;
            Serial.println(F("\033[0;32m[OK] ACCESS MAXIMALE ACCORDE (Mode Root Actif).\033[0m"));
        } else {
            Serial.println(F("\033[0;31m[ERROR] Mot de passe incorrect.\033[0m"));
        }
        return;
    }

    // -------------------------------------------------------------------------
    // 💻 CONSOLE MODE SPECIFIC (arduino@uno$)
    // -------------------------------------------------------------------------
    if (currentMode == MODE_CONSOLE) {
        
        if (cmd == F("cd SETUP")) {
            currentMode = MODE_SETUP;
            Serial.println(F("[SYSTEM] Configuration active. Entrez vos commandes SETUP."));
        }
        else if (cmd == F("reboot")) {
            if (!isSuperUser) { Serial.println(F("\033[0;31m[ERROR] Droits insuffisants. su -C requis.\033[0m")); return; }
            Serial.println(F("\033[0;31m[!] Hardware Respring/Reboot...\033[0m")); delay(400);
            void(* resetFunc) (void) = 0; resetFunc(); 
        }
        else if (cmd == F("killall -9 System DOS")) {
            if (!isSuperUser) { Serial.println(F("\033[0;31m[ERROR] Action critique. su -C requis.\033[0m")); return; }
            Serial.println(F("\033[0;31m[!] Halting Kernel. System DOS Mort.\033[0m")); while(true);
        }
        else if (cmd == F("@exit arduino@uno") || cmd == F("mnt.2.bxv") || cmd == F("cd ~/user")) {
            Serial.println(F("\033[0;33mExiting Console Mode... Switching to base_use$\033[0m"));
            currentMode = MODE_USER; isSuperUser = false;
        }
        else if (cmd == F("cd ~/administrator")) {
            Serial.println(F("\033[0;32m[OK] Entree directe dans la racine admin.\033[0m"));
        }
        else if (cmd.startsWith(F("git"))) {
            Serial.println(F("[Git Hub] Info Science: Repository synchronise en lecture brute."));
        }
        else if (cmd.startsWith(F("cipher")) || cmd.startsWith(F("decipher"))) {
            Serial.println(F("[Consolism] Cryptoprocesseur actif : Traitement du flux binaire fini."));
        }
        else if (cmd == F("@backup \"arduino@uno\"")) {
            Serial.println(F("[Backup] Sauvegarde complete generee."));
        }
        else if (cmd == F("@save & reset defaults")) {
            Serial.println(F("[Reset] Remise a zero des parametres par defaut accomplie."));
        }
        else if (cmd == F("@reset & unmount")) {
            Serial.println(F("\033[0;31m[Restore Factory] Purge complete de la memoire EEPROM...\033[0m"));
            for (int i = 0 ; i < EEPROM.length() ; i++) { EEPROM.write(i, 0); }
            Serial.println(F("[Done] Remise a l'état d'usine terminee."));
        }
        else { Serial.println(F("\033[0;31mCommand Not found or Unsupported Mode\033[0m")); }
    }
    
    // -------------------------------------------------------------------------
    // 🎮 USER MODE SPECIFIC (base_use$)
    // -------------------------------------------------------------------------
    else if (currentMode == MODE_USER) {
        if (cmd == F("open jeu") || cmd == F("jeux")) {
            Serial.println(F("[User] Lancement de l'application de jeu... Tapez '@exit' pour fermer."));
        }
        else if (cmd.startsWith(F("copie")) || cmd.startsWith(F("deplace"))) {
            Serial.println(F("[User] Action de fichier traditionnelle reussie."));
        }
        else if (cmd == F("@exit") || cmd == F("@end") || cmd == F("cd & mount.2.mvx") || cmd == F("cd /mount2/MVX")) {
            Serial.println(F("\033[0;33mDémontage de session utilisateur... Retour à arduino@uno$\033[0m"));
            currentMode = MODE_CONSOLE;
        }
        else { Serial.println(F("\033[0;31mCommand Not found or Unsupported Mode\033[0m")); }
    }
}
