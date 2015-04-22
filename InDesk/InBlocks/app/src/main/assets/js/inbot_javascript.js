Blockly.JavaScript['drive_move'] = function(block) {
  var dropdown_move = block.getFieldValue('MOVE');
  var dropdown_by = block.getFieldValue('BY');
  // TODO: Assemble JavaScript into code variable.
  var code = dropdown_move + '(' + dropdown_by + ');\n';
  return code;
}; 

Blockly.JavaScript['sound_play'] = function(block) {
  var dropdown_note = block.getFieldValue('NOTE');
  var dropdown_beat = block.getFieldValue('BEAT');
  // TODO: Assemble JavaScript into code variable.
  var code = 'play("' + dropdown_note + '",' + dropdown_beat + ');\n';
  return code;
};