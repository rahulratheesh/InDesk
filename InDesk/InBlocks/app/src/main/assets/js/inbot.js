Blockly.Blocks['drive_move'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(120);
    this.appendDummyInput()
        .appendField("move")
        .appendField(new Blockly.FieldDropdown([["forward", "moveForward"], ["backward", "moveBackward"]]), "MOVE")
        .appendField("by")
        .appendField(new Blockly.FieldDropdown([["10", "1000"], ["20", "2000"], ["30", "3000"], ["40", "4000"], ["50", "5000"]]), "BY");
    this.setInputsInline(true);
    this.setPreviousStatement(true, "null");
    this.setNextStatement(true, "null");
    this.setTooltip('');
  }
};

Blockly.Blocks['sound_play'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(210);
    this.appendDummyInput()
        .appendField("play");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["c", "c"], ["d", "d"], ["e", "e"], ["f", "f"], ["g", "g"], ["a", "a"], ["b", "b"], ["C", "C"], ["-", "-"]]), "NOTE");
    this.appendDummyInput()
        .appendField("with beat");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["1", "1"], ["2", "2"], ["3", "3"], ["4", "4"], ["5", "5"]]), "BEAT");
    this.setInputsInline(true);
    this.setPreviousStatement(true, "null");
    this.setNextStatement(true, "null");
    this.setTooltip('');
  }
};