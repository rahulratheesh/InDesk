Blockly.JavaScript['drive_forward'] = function(block) {
  var dropdown_time = block.getFieldValue('TIME');
  var dropdown_speed = block.getFieldValue('SPEED');
  // TODO: Assemble JavaScript into code variable.
  var code = 'forward("' + dropdown_time + '","' + dropdown_speed + '");\n';
  return code;
}; 

Blockly.JavaScript['drive_backward'] = function(block) {
  var dropdown_time = block.getFieldValue('TIME');
  var dropdown_speed = block.getFieldValue('SPEED');
  // TODO: Assemble JavaScript into code variable.
  var code = 'backward("' + dropdown_time + '","' + dropdown_speed + '");\n';
  return code;
}; 

Blockly.JavaScript['drive_left'] = function(block) {
  var dropdown_angle = block.getFieldValue('ANGLE');
  // TODO: Assemble JavaScript into code variable.
  var code = 'left("' + dropdown_angle + '");\n';
  return code;
}; 

Blockly.JavaScript['drive_right'] = function(block) {
  var dropdown_angle = block.getFieldValue('ANGLE');
  // TODO: Assemble JavaScript into code variable.
  var code = 'right("' + dropdown_angle + '");\n';
  return code;
}; 


Blockly.JavaScript['drive_stop'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  var code = 'stopWheels();\n';
  return code;
};

Blockly.JavaScript['sound_play'] = function(block) {
  var dropdown_note = block.getFieldValue('NOTE');
  var dropdown_beat = block.getFieldValue('BEAT');
  // TODO: Assemble JavaScript into code variable.
  var code = 'play("' + dropdown_note + '",' + dropdown_beat + ');\n';
  return code;
};

Blockly.JavaScript['control_repeat'] = function(block) {
  var repeats = block.getFieldValue('TIMES');
  var branch = Blockly.JavaScript.statementToCode(block, 'DO');
  // TODO: Assemble JavaScript into code variable.
  branch = Blockly.JavaScript.addLoopTrap(branch, block.id);
  var loopVar = Blockly.JavaScript.variableDB_.getDistinctName(
        'count', Blockly.Variables.NAME_TYPE);
  var code = 'for (var ' + loopVar + ' = 0; ' +
        loopVar + ' < ' + repeats + '; ' +
        loopVar + '++) {\n' +
        branch + '}\n';
  return code;
};