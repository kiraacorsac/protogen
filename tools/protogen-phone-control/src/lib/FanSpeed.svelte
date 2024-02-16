<script lang="ts">
  import ProtogenConfirmationButton from "./ProtogenConfirmationButton.svelte";

  export let url;
  let selectedSpeed = 10;
</script>

<div class="slidecontainer">
  <input type="range" min="0" max="255" bind:value={selectedSpeed} />
  {selectedSpeed}
</div>

<ProtogenConfirmationButton
  path="fanSpeed"
  title="Set Fan Speed"
  {url}
  value={selectedSpeed}
/>

<style>
</style>
