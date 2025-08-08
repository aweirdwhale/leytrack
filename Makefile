# Configuration
BOARD_FQBN = esp32:esp32:esp32
PORT = /dev/ttyUSB0
PROJECT_DIR = $(CURDIR)
BIN_PREFIX = leytrack.ino
BUILD_DIR = build
# Dossier de logs
LOG_DIR = dist/logs
DATE := $(shell date +"%Y-%m-%d_%H-%M-%S")

BAUD = 115200

$(shell mkdir -p $(LOG_DIR))
$(shell mkdir -p $(BUILD_DIR))

clean:
		rm -rf $(BUILD_DIR)

	# Compilation
compile:
		@echo "🔧 Compilation du projet..."
		make clean
		arduino-cli compile --fqbn $(BOARD_FQBN) --output-dir $(BUILD_DIR) $(PROJECT_DIR) 2>&1 | tee $(LOG_DIR)/compile_$(DATE).log

# Upload (avec esptool)
upload:
	@echo "🚀 Upload du .bin compilé dans build..."
	esptool.py --chip esp32 --port $(PORT) --baud $(BAUD) write_flash -z \
		0x1000 $(BUILD_DIR)/$(BIN_PREFIX).bootloader.bin \
		0x8000 $(BUILD_DIR)/$(BIN_PREFIX).partitions.bin \
		0x10000 $(BUILD_DIR)/$(BIN_PREFIX).bin | tee $(LOG_DIR)/upload_$(DATE).log

monitor:
	@echo "🚀 Moniteur du port série..."
	arduino-cli monitor -p $(PORT) --config $(BAUD)

# Compilation + Upload
flash: compile upload

# Installation d'une bibliothèque
install:
	ifndef LIB
			$(error Utilisation: make install LIB=NomDeLaLib)
	endif
			@echo "📦 Installation de la lib $(LIB)..."
			arduino-cli lib install $(LIB)

# Nettoyage des logs
clean-logs:
		rm -f $(LOG_DIR)/*.log

# Change le port de connexion
new-port:
		@echo "🔧 Change le port de connexion..."
		@echo "Entrez le nouveau port:"
		read PORT
		@echo "Nouveau port: $(PORT)"

clean-esp:
		@echo "🧹 Nettoyage de l'ESP32..."
		esptool.py --chip esp32 --port $(PORT) --baud $(BAUD) erase_flash 2>&1 | tee $(LOG_DIR)/clean_esp_$(DATE).log

# Aide
help:
		@echo "Commandes disponibles:"
		@echo "  make compile           # Compile le projet"
		@echo "  make upload            # Upload vers l'ESP32"
		@echo "  make flash             # Compile + upload"
		@echo "  make install LIB=xxx   # Installe une bibliothèque Arduino"
		@echo "  make clean-logs        # Supprime les logs"
		@echo "  make new-port          # Change le port de connexion"
		@echo "  make clean             # Supprime le dossier build"
		@echo "  make clean-esp         # Nettoyage de l'ESP32"
		@echo "  make monitor           # Ouvre la console du port série"
