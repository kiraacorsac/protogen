<script lang="ts">
  import ProtogenConfirmationButton from "./ProtogenConfirmationButton.svelte";

  export let url;
  let maxBrightness = 100;
  let selectedBrightness = 10;
</script>

Max Brightness: <input
  type="number"
  min="0"
  max="255"
  bind:value={maxBrightness}
/>
<div class="slidecontainer">
  <input
    type="range"
    min="0"
    max={maxBrightness}
    bind:value={selectedBrightness}
  />
  {selectedBrightness}
</div>

<ProtogenConfirmationButton
  path="brightness"
  title="Set Brightness"
  {url}
  value={selectedBrightness}
/>

<style>
</style>
