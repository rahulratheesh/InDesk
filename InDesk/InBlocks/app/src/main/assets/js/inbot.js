Blockly.Blocks['drive_forward'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(195);
    this.appendDummyInput()
        .appendField("Forward  ");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["1", "1000"], ["2", "2000"], ["3", "3000"]]), "TIME");
    this.appendDummyInput()
        .appendField("s  Speed");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["slow", "100"], ["normal", "200"], ["fast", "255"]]), "SPEED");
    this.setInputsInline(true);
    this.setPreviousStatement(true, "null");
    this.setNextStatement(true, "null");
    this.setTooltip('');
  }
};

Blockly.Blocks['drive_backward'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(195);
    this.appendDummyInput()
        .appendField("Backward  ");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["1", "1000"], ["2", "2000"], ["3", "3000"]]), "TIME");
    this.appendDummyInput()
        .appendField("s  Speed");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["slow", "100"], ["normal", "200"], ["fast", "255"]]), "SPEED");
    this.setInputsInline(true);
    this.setPreviousStatement(true, "null");
    this.setNextStatement(true, "null");
    this.setTooltip('');
  }
};

Blockly.Blocks['drive_left'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(195);
    this.appendDummyInput()
        .appendField("Turn Left  ");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["250", "200"], ["500", "500"], ["750", "750"], ["1000", "1000"]]), "ANGLE");
    this.appendDummyInput()
        .appendField("  ms");
    this.setInputsInline(true);
    this.setPreviousStatement(true, "null");
    this.setNextStatement(true, "null");
    this.setTooltip('');
  }
};

Blockly.Blocks['drive_right'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(195);
    this.appendDummyInput()
        .appendField("Turn Right  ");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["250", "200"], ["500", "500"], ["750", "750"], ["1000", "1000"]]), "ANGLE");
    this.appendDummyInput()
        .appendField("  ms");
    this.setInputsInline(true);
    this.setPreviousStatement(true, "null");
    this.setNextStatement(true, "null");
    this.setTooltip('');
  }
};

Blockly.Blocks['drive_stop'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(195);
    this.appendDummyInput()
        .appendField("Stop Wheels");
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
        .appendField("Play");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["c", "c"], ["d", "d"], ["e", "e"], ["f", "f"], ["g", "g"], ["a", "a"], ["b", "b"], ["C", "C"], ["-", "-"]]), "NOTE");
    this.appendDummyInput()
        .appendField("with Beat");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["1", "1"], ["2", "2"], ["3", "3"], ["4", "4"], ["5", "5"]]), "BEAT");
    this.setInputsInline(true);
    this.setPreviousStatement(true, "null");
    this.setNextStatement(true, "null");
    this.setTooltip('');
  }
};

Blockly.Blocks['control_repeat'] = {
  init: function() {
    this.setHelpUrl('http://www.example.com/');
    this.setColour(330);
    this.appendDummyInput()
        .appendField("Repeat ");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["2", "2"], ["3", "3"], ["4", "4"], ["5", "5"]]), "TIMES");
    this.appendDummyInput()
        .appendField("  times");
    this.appendStatementInput("DO");
    this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
    this.setTooltip('');
  }
};

