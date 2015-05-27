package edu.iiitb.inblocks;

/**
 * Created by rahul on 11/2/15.
 */
public class Shaders
{
    public static final String VERTEX_SHADER = " \n" + "\n"
            + "attribute vec4 vertexPosition; \n"
            + "attribute vec4 vertexNormal; \n"
            + "attribute vec2 vertexTexCoord; \n" + "\n"
            + "varying vec2 texCoord; \n" + "varying vec4 normal; \n" + "\n"
            + "uniform mat4 modelViewProjectionMatrix; \n" + "\n"
            + "void main() \n" + "{ \n"
            + "   gl_Position = modelViewProjectionMatrix * vertexPosition; \n"
            + "   normal = vertexNormal; \n" + "   texCoord = vertexTexCoord; \n"
            + "} \n";

    public static final String FRAGMENT_SHADER = " \n" + "\n"
            + "precision mediump float; \n" + " \n" + "varying vec2 texCoord; \n"
            + "varying vec4 normal; \n" + " \n"
            + "uniform sampler2D texSampler2D; \n" + " \n" + "void main() \n"
            + "{ \n" + "   gl_FragColor = texture2D(texSampler2D, texCoord); \n"
            + "} \n";
}
