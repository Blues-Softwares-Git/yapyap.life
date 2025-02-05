/**
 * @file capture_video.c
 * @brief Capture vidéo à l'aide de GStreamer et NVENC (pour NVIDIA).
 *
 * Ce fichier définit la fonction void capture_video() qui initialise GStreamer,
 * crée une pipeline de capture vidéo depuis une caméra, convertit le flux, encode
 * la vidéo en H264 avec l'encodeur matériel NVENC, et sauvegarde le résultat dans
 * un fichier MP4.
 *
 * La pipeline utilisée est la suivante (pour Linux) :
 *   v4l2src ! videoconvert ! nvh264enc ! h264parse ! mp4mux ! filesink
 *
 * Pour Windows, il faudra remplacer "v4l2src" par "dshow" et adapter les propriétés
 * en fonction de la configuration de la caméra.
 *
 * @note Pour compiler ce programme, vous devez avoir GStreamer installé avec ses plugins.
 *
 * Compilation sous Linux (avec pkg-config) :
 * @code
 * gcc -o capture_video capture_video.c `pkg-config --cflags --libs gstreamer-1.0`
 * @endcode
 *
 * Exécution :
 * @code
 * ./capture_video
 * @endcode
 *
 * @author
 * Major_Ghz
 * @date 2025-02-05
 */

#include <gst/gst.h>
#include <stdio.h>

/**
 * @brief Capture et enregistre une vidéo à partir de la caméra.
 *
 * La fonction initialise GStreamer, crée et configure une pipeline pour la capture
 * vidéo en utilisant l'élément "v4l2src" (pour Linux). La vidéo est convertie via
 * "videoconvert", encodée en H264 avec "nvh264enc" (encodeur NVENC pour les GPU NVIDIA),
 * puis parsée avec "h264parse", multiplexée dans un fichier MP4 via "mp4mux", et enfin
 * enregistrée avec "filesink".
 *
 * La fonction configure également le bitrate de l'encodeur à 4000 kbps (4 Mbps) et
 * attend la fin du flux ou une erreur pour terminer la capture.
 *
 * @return void
 */
void capture_video() {
    GstElement *pipeline, *source, *convert, *encoder, *parser, *mux, *sink;
    GstBus *bus;
    GstMessage *msg;
    GstStateChangeReturn ret;

    // Initialisation de GStreamer
    gst_init(NULL, NULL);

    // Création de la pipeline
    pipeline = gst_pipeline_new("video-capture-pipeline");

    // Création des éléments :
    // - source: capture le flux vidéo de la caméra (v4l2src pour Linux)
    // - convert: convertit le format vidéo si nécessaire
    // - encoder: encode le flux en H264 avec NVENC (pour les GPU NVIDIA)
    // - parser: prépare le flux H264 pour le multiplexage
    // - mux: multiplexe le flux dans un conteneur MP4
    // - sink: enregistre le flux dans un fichier
    source   = gst_element_factory_make("v4l2src", "source");
    convert  = gst_element_factory_make("videoconvert", "convert");
    encoder  = gst_element_factory_make("nvh264enc", "encoder");
    parser   = gst_element_factory_make("h264parse", "parser");
    mux      = gst_element_factory_make("mp4mux", "muxer");
    sink     = gst_element_factory_make("filesink", "sink");

    // Vérification que tous les éléments ont été créés
    if (!pipeline || !source || !convert || !encoder || !parser || !mux || !sink) {
        g_printerr("Erreur: Impossible de créer tous les éléments de la pipeline.\n");
        return;
    }

    // Configuration de l'élément filesink : définir le fichier de sortie
    g_object_set(sink, "location", "output.mp4", NULL);

    // Configuration de l'encodeur NVENC : fixer le bitrate à 4000 kbps (4 Mbps)
    g_object_set(encoder, "bitrate", 4000, NULL);

    // Ajout des éléments à la pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, convert, encoder, parser, mux, sink, NULL);

    // Liaison des éléments dans l'ordre
    if (!gst_element_link(source, convert)) {
        g_printerr("Erreur de liaison: source -> convert\n");
        gst_object_unref(pipeline);
        return;
    }
    if (!gst_element_link(convert, encoder)) {
        g_printerr("Erreur de liaison: convert -> encoder\n");
        gst_object_unref(pipeline);
        return;
    }
    if (!gst_element_link(encoder, parser)) {
        g_printerr("Erreur de liaison: encoder -> parser\n");
        gst_object_unref(pipeline);
        return;
    }
    if (!gst_element_link(parser, mux)) {
        g_printerr("Erreur de liaison: parser -> mux\n");
        gst_object_unref(pipeline);
        return;
    }
    if (!gst_element_link(mux, sink)) {
        g_printerr("Erreur de liaison: mux -> sink\n");
        gst_object_unref(pipeline);
        return;
    }

    // Passage de la pipeline à l'état PLAYING
    ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("Erreur: Impossible de lancer la pipeline.\n");
        gst_object_unref(pipeline);
        return;
    }

    // Récupération du bus de la pipeline pour surveiller les messages (erreur ou fin du flux)
    bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                     GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    // Traitement du message reçu
    if (msg != NULL) {
        GError *err;
        gchar *debug_info;

        switch (GST_MESSAGE_TYPE(msg)) {
            case GST_MESSAGE_ERROR:
                gst_message_parse_error(msg, &err, &debug_info);
                g_printerr("Erreur de l'élément %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
                g_printerr("Infos de débogage: %s\n", debug_info ? debug_info : "aucune");
                g_clear_error(&err);
                g_free(debug_info);
                break;
            case GST_MESSAGE_EOS:
                g_print("Fin du flux (EOS) atteinte.\n");
                break;
            default:
                g_printerr("Message inattendu reçu.\n");
                break;
        }
        gst_message_unref(msg);
    }

    // Libération des ressources
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
}

#ifdef TEST_CAPTURE_VIDEO
/**
 * @brief Fonction principale pour tester capture_video().
 *
 * Compilez avec la macro TEST_CAPTURE_VIDEO définie (par exemple, avec -DTEST_CAPTURE_VIDEO)
 * pour exécuter ce test.
 */
int main(int argc, char *argv[]) {
    capture_video();
    return 0;
}
#endif
