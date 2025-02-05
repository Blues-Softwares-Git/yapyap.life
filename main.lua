-- main.lua
-- Ce script utilise le module video_capture pour lancer la capture vidéo
-- via GStreamer, et utilise Love2D pour l'interface graphique.

-- Charger le module de capture vidéo.
local vc = require("video_capture")

function love.load()
    -- Configuration de la fenêtre
    love.window.setMode(800, 600, {resizable = false})
    love.window.setTitle("Video Capture with Love2D and GStreamer")

    -- Démarrage de la capture vidéo.
    -- Note : Cette opération peut être bloquante, car elle exécute une commande système.
    vc.capture_video()
end

function love.draw()
    -- Afficher un message pour informer l'utilisateur.
    love.graphics.printf("La capture vidéo a été lancée.\nVérifiez le fichier 'output.mp4' pour voir le résultat.", 0, 50, love.graphics.getWidth(), "center")
end

function love.update(dt)
    -- Ici, vous pouvez ajouter une logique de mise à jour si nécessaire.
end

