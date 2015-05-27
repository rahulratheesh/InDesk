package edu.iiitb.inblocks;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.util.Log;

/**
 * Created by rahul on 24/5/15.
 */
public class InBot
{
    private float travelled = 0;
    private float heading = 0;

    private boolean executing = false;
    float[] pose = {0, 0, 0};

    private int duration = 1; // seconds
    private final int sampleRate = 8000;
    private final int numSamples = duration * sampleRate;
    private final double sample[] = new double[numSamples];
//    private final double freqOfTone = 1915; // hz

    private final double freqOfTone[] = {956, 1014, 1136, 1275, 1432, 1519, 1700, 1915};
    private final byte generatedSnd[] = new byte[2 * numSamples];

    public float[] forward(float distance, float headingAngle) {
        executing = false;
        if (travelled < distance) {
            executing = true;
            travelled += 0.1f;
            float dx = (float) (0.1f * Math.sin(Math.toRadians(headingAngle)));
            float dz = (float) (0.1f * Math.cos(Math.toRadians(headingAngle)));

            pose[0] = dx;
            pose[1] = dz;
            pose[2] = heading;

        } else {
            travelled = 0f;
        }

        return pose;
    }

    public float[] backward(float distance, float headingAngle) {
        executing = false;
        if (travelled < distance) {
            executing = true;
            travelled += 0.1f;
            float dx = (float) (0.1f * Math.sin(Math.toRadians(headingAngle)));
            float dz = (float) (0.1f * Math.cos(Math.toRadians(headingAngle)));

            pose[0] = -dx;
            pose[1] = -dz;
            pose[2] = heading;

        } else {
            travelled = 0f;
        }

        return pose;
    }

    public float[] left(float angle) {
        executing = false;
        if (heading < angle) {
            executing = true;
            heading += 1f;
            heading %= 360;

            pose[0] = 0;
            pose[1] = 0;
            pose[2] = 1f;

        } else {
            heading = 0;
        }

        return pose;
    }

    public float[] right(float angle) {
        executing = false;

        if (heading < angle) {
            executing = true;
            heading += 1f;
            heading %= 360;

            pose[0] = 0;
            pose[1] = 0;
            pose[2] = 1f;

        } else {
            heading = 0;
        }

        return pose;
    }

    void genTone(double freqOfTone){
        // fill out the array
        for (int i = 0; i < numSamples; ++i) {
            sample[i] = Math.sin(2 * Math.PI * i / (sampleRate/freqOfTone));
        }

        // convert to 16 bit pcm sound array
        // assumes the sample buffer is normalised.
        int idx = 0;
        for (final double dVal : sample) {
            // scale to maximum amplitude
            final short val = (short) ((dVal * 32767));
            // in 16 bit wav PCM, first byte is the low order byte
            generatedSnd[idx++] = (byte) (val & 0x00ff);
            generatedSnd[idx++] = (byte) ((val & 0xff00) >>> 8);

        }
    }

    void playSound(){
        final AudioTrack audioTrack = new AudioTrack(AudioManager.STREAM_MUSIC,
                sampleRate, AudioFormat.CHANNEL_OUT_MONO,
                AudioFormat.ENCODING_PCM_16BIT, generatedSnd.length/4,
                AudioTrack.MODE_STATIC);
        audioTrack.write(generatedSnd, 0, generatedSnd.length/4);
        audioTrack.play();
    }

    void playNote(String note, String duration) {
        Log.i("InBot", note + " " + duration);
//        this.duration = Integer.parseInt(duration);
        executing = true;
        char noteChar = note.charAt(0);
        double freq = 0;
        switch (noteChar)
        {
            case 'c':
                freq = freqOfTone[0];
                break;
            case 'd':
                freq = freqOfTone[1];
                break;
            case 'e':
                freq = freqOfTone[2];
                break;
            case 'f':
                freq = freqOfTone[3];
                break;
            case 'g':
                freq = freqOfTone[4];
                break;
            case 'a':
                freq = freqOfTone[5];
                break;
            case 'b':
                freq = freqOfTone[6];
                break;
            case 'C':
                freq = freqOfTone[7];
                break;
            case '-':
                freq = 0;
                break;
        }
        genTone(freq);
        playSound();
        executing = false;
    }

    public boolean isExecuting() {
        return executing;
    }


    private String[] parseCommand(String command)
    {
        String[] commandArr = new String[3];

        int spaceIndex = command.indexOf(" ");
        commandArr[0] = command.substring(0, spaceIndex);
        String arguments = command.substring(spaceIndex + 1);
        spaceIndex = arguments.indexOf(" ");
        commandArr[1] = arguments.substring(0, spaceIndex);
        commandArr[2] = arguments.substring(spaceIndex + 1);

        return commandArr;
    }

    public float[] process(String command, float heading) {

        Log.i("InBot", command);
        String[] commandArr = parseCommand(command);

        if (commandArr[0].equals("PLAY")) {
            playNote(commandArr[1], commandArr[2]);
        }

//        if (command == "1") {
//            pose = forward(10f, heading);
//        } else if (command == "2") {
//            pose = backward(10f, heading);
//        } else if (command == "3") {
//            pose = left(90f);
//        } else if (command == "4") {
//            pose = right(90f);
//        }

        return pose;
    }

}
