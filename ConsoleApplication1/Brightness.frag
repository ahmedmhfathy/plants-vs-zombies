uniform sampler2D texture; // The sprite's texture
uniform float brightness;  // Brightness multiplier

void main() {
    vec4 textureColor = texture2D(texture, gl_TexCoord[0].xy);

    vec4 tintedColor = textureColor * gl_Color; // gl_Color holds the sf::Sprite::getColor() value

    gl_FragColor = vec4(tintedColor.rgb * brightness, tintedColor.a);
}
